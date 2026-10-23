#include "Pantalla.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"

// CONSTRUCTOR
//
// Guarda los GPIO de control
// y las dimensiones que utilizaremos.
//
// Todavia no configura el hardware.

Pantalla::Pantalla(unsigned int cs, unsigned int dc) {
    pinCS = cs;
    pinDC = dc;

    ancho = 320;
    alto = 240;
}

// COMANDO
//
// D/C en 0 significa:
// lo que enviamos es una instruccion.
//
// CS en 0 selecciona la pantalla.
// CS en 1 termina esta comunicacion.

void Pantalla::comando(uint8_t valor) {
    gpio_put(pinDC, 0);
    gpio_put(pinCS, 0);

    spi_write_blocking(spi0, &valor, 1);

    gpio_put(pinCS, 1);
}

// DATO
//
// D/C en 1 significa:
// lo que enviamos es un dato.
//
// Puede ser parte de una coordenada,
// un color o una configuracion.

void Pantalla::dato(uint8_t valor) {
    gpio_put(pinDC, 1);
    gpio_put(pinCS, 0);

    spi_write_blocking(spi0, &valor, 1);

    gpio_put(pinCS, 1);
}

// VENTANA
//
// Selecciona el area que vamos a pintar.
//
// Puede ser toda la pantalla
// o solamente un pixel.
//
// Cada coordenada se envia en dos bytes:
// primero la parte alta y despues la baja.

void Pantalla::ventana(int x0, int y0, int x1, int y1) {
    // Seleccionar columnas.
    comando(0x2A);

    dato(x0 >> 8);
    dato(x0 & 0xFF);
    dato(x1 >> 8);
    dato(x1 & 0xFF);

    // Seleccionar filas.
    comando(0x2B);

    dato(y0 >> 8);
    dato(y0 & 0xFF);
    dato(y1 >> 8);
    dato(y1 & 0xFF);

    // Preparar la escritura de los pixeles.
    comando(0x2C);
}

// INICIAR
//
// Usaremos el periferico SPI0.
//
// GP18: reloj.
// GP19: salida de datos.
//
// CS y D/C seran salidas digitales normales.

void Pantalla::iniciar() {
    gpio_init(pinCS);
    gpio_put(pinCS, 1);
    gpio_set_dir(pinCS, GPIO_OUT);

    gpio_init(pinDC);
    gpio_put(pinDC, 1);
    gpio_set_dir(pinDC, GPIO_OUT);

    // Comunicacion SPI a 10 MHz.
    spi_init(spi0, 10000000);

    gpio_set_function(18, GPIO_FUNC_SPI);
    gpio_set_function(19, GPIO_FUNC_SPI);

    // Enviamos bytes de 8 bits,
    // comenzando por el bit mas significativo.
    spi_set_format(
        spi0,
        8,
        SPI_CPOL_0,
        SPI_CPHA_0,
        SPI_MSB_FIRST
    );

    // Reinicio mediante una instruccion.
    comando(0x01);
    sleep_ms(150);

    // Salir del modo de reposo.
    comando(0x11);
    sleep_ms(120);

    // Color RGB565:
    // cada pixel utiliza 16 bits.
    comando(0x3A);
    dato(0x55);

    // Orientacion horizontal:
    // ancho 320 y alto 240.
    comando(0x36);
    dato(0x28);

    // Encender la imagen.
    comando(0x29);
    sleep_ms(20);
}

// LIMPIAR
//
// Pintamos toda la pantalla del mismo color.
//
// Enviamos bloques de pixeles para evitar
// una comunicacion separada por cada pixel.

void Pantalla::limpiar(uint16_t color) {

    // Tambien limpiamos la memoria del dibujo.
    //
    // En este proyecto utilizamos:
    // 0x0000: negro.
    // 0xFFFF: blanco.
    uint8_t relleno = 0x00;

    if (color == 0xFFFF) {
        relleno = 0xFF;
    }

    for (int i = 0; i < 9600; i++) {
        dibujo[i] = relleno;
    }

    ventana(0, 0, ancho - 1, alto - 1);

    // Cada pixel ocupa dos bytes.
    // Este bloque contiene 128 pixeles.
    uint8_t bloque[256];

    for (int i = 0; i < 256; i += 2) {
        bloque[i] = color >> 8;
        bloque[i + 1] = color & 0xFF;
    }

    gpio_put(pinDC, 1);
    gpio_put(pinCS, 0);

    int pendientes = ancho * alto;

    while (pendientes > 0) {
        int cantidad = pendientes;

        if (cantidad > 128) {
            cantidad = 128;
        }

        spi_write_blocking(spi0, bloque, cantidad * 2);

        pendientes -= cantidad;
    }

    gpio_put(pinCS, 1);
}

// PIXEL DIRECTO
//
// Escribe en la pantalla sin guardar el cambio.
//
// Lo usaremos para mostrar el cursor
// sin que pase a formar parte del dibujo.

void Pantalla::pixelDirecto(int x, int y, uint16_t color) {
    if (x < 0 || x >= ancho || y < 0 || y >= alto) {
        return;
    }

    ventana(x, y, x, y);

    dato(color >> 8);
    dato(color & 0xFF);
}

// PUNTO
//
// Guarda el pixel en la memoria del dibujo
// y despues lo muestra en la pantalla.
//
// Esta memoria esta preparada para nuestro
// dibujo en blanco sobre fondo negro.

void Pantalla::punto(int x, int y, uint16_t color) {
    if (x < 0 || x >= ancho || y < 0 || y >= alto) {
        return;
    }

    // Convertimos la coordenada en una posicion
    // dentro de la memoria.
    int posicion = y * ancho + x;

    // Cada byte guarda ocho pixeles.
    int indice = posicion / 8;
    uint8_t mascara = 1u << (posicion % 8);

    if (color == 0xFFFF) {
        // Guardamos un pixel blanco.
        dibujo[indice] |= mascara;
    } else {
        // Guardamos un pixel negro.
        dibujo[indice] &= ~mascara;
    }

    pixelDirecto(x, y, color);
}

// LINEA
//
// Al mover una perilla, la coordenada puede
// saltar varios pixeles entre dos lecturas.
//
// Si solo dibujamos la nueva posicion,
// quedarian espacios entre los puntos.
//
// Por eso dibujaremos todos los pixeles
// necesarios para unir ambas posiciones.
//
// Utilizamos el algoritmo de Bresenham.
// Permite dibujar lineas con numeros enteros.

void Pantalla::linea(
    int x0, int y0,
    int x1, int y1,
    uint16_t color
) {
    // Calculamos la distancia horizontal.
    int distanciaX = x1 - x0;

    // Queremos la distancia sin signo negativo.
    if (distanciaX < 0) {
        distanciaX = -distanciaX;
    }

    // Calculamos la distancia vertical.
    int distanciaY = y1 - y0;

    if (distanciaY < 0) {
        distanciaY = -distanciaY;
    }

    // Elegimos el sentido del avance horizontal.
    //
    //  1: hacia la derecha.
    // -1: hacia la izquierda.
    int pasoX = 1;

    if (x0 > x1) {
        pasoX = -1;
    }

    // Elegimos el sentido del avance vertical.
    //
    //  1: hacia abajo.
    // -1: hacia arriba.
    int pasoY = 1;

    if (y0 > y1) {
        pasoY = -1;
    }

    // Este valor ayuda a decidir cuando
    // avanzar en X, en Y o en ambos.
    //
    // Es un calculo del algoritmo:
    // no significa que el programa tenga un fallo.
    int error = distanciaX - distanciaY;

    while (true) {
        // Dibujamos el pixel actual.
        punto(x0, y0, color);

        // Si llegamos al destino,
        // terminamos la linea.
        if (x0 == x1 && y0 == y1) {
            break;
        }

        // Guardamos el calculo antes de modificarlo.
        int dobleError = 2 * error;

        // Comprobamos si debemos avanzar en X.
        if (dobleError > -distanciaY) {
            error -= distanciaY;
            x0 += pasoX;
        }

        // Comprobamos si debemos avanzar en Y.
        //
        // Son dos if independientes porque
        // en una diagonal podemos avanzar
        // en ambos ejes durante la misma vuelta.
        if (dobleError < distanciaX) {
            error += distanciaX;
            y0 += pasoY;
        }
    }
}

// CURSOR
//
// Mostramos una cruz amarilla de cinco pixeles
// de ancho y cinco de alto.
//
// mostrar == true:
// pintamos la cruz sin modificar el dibujo.
//
// mostrar == false:
// recuperamos el color original de cada pixel.
//
// En los bordes solo pintamos la parte
// de la cruz que queda dentro de la pantalla.

void Pantalla::cursor(int x, int y, bool mostrar) {
    for (int desplazamiento = -2;
         desplazamiento <= 2;
         desplazamiento++) {

        // Revisamos un punto del brazo horizontal
        // y otro del brazo vertical.
        for (int eje = 0; eje < 2; eje++) {
            int px = x;
            int py = y;

            if (eje == 0) {
                px += desplazamiento;
            } else {
                py += desplazamiento;
            }

            if (px < 0 || px >= ancho ||
                py < 0 || py >= alto) {
                continue;
            }

            uint16_t color;

            if (mostrar) {
                // Amarillo en formato RGB565.
                color = 0xFFE0;
            } else {
                // Recuperamos el pixel del dibujo.
                int posicion = py * ancho + px;
                int indice = posicion / 8;

                uint8_t mascara =
                    1u << (posicion % 8);

                if ((dibujo[indice] & mascara) != 0) {
                    color = 0xFFFF;
                } else {
                    color = 0x0000;
                }
            }

            pixelDirecto(px, py, color);
        }
    }
}