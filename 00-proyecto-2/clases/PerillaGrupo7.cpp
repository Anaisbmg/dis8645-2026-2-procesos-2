//CODIGO HECHO CON CLAUDE PARA TESTEAR EL FUNCIONAMIENTO DEL CIRCUITO EN WOKWI//

// ============================================================
// TRAZO - Código de PRUEBA del cableado (versión 2)
// Qué comprueba:
//   1) Las dos perillas (GP26 y GP27) leyendo valores de 0 a 4095
//   2) Los dos botones (GP14 y GP15)
//   3) Que la pantalla OLED responde por I2C (GP4 y GP5) y dibuja
// Los resultados salen por el monitor serial de Wokwi.
// ============================================================

#include <stdio.h>            // para usar printf (escribir en el monitor serial)
#include "pico/stdlib.h"      // funciones básicas de la Pico (gpio, sleep_ms, etc.)
#include "hardware/adc.h"     // para leer las perillas (entradas analógicas)
#include "hardware/i2c.h"     // para hablar con la pantalla

// ---------- Pines (los mismos del dibujo) ----------
const int PIN_SDA = 4;               // cable verde de la pantalla
const int PIN_SCL = 5;               // cable amarillo de la pantalla
const int PIN_BOTON_TRAZO = 14;      // botón de arriba (celeste)
const int PIN_BOTON_BORRAR = 15;     // botón de abajo (rosado)
const int PIN_PERILLA_H = 26;        // perilla horizontal (entrada ADC 0)
const int PIN_PERILLA_V = 27;        // perilla vertical (entrada ADC 1)

// Dirección de la pantalla SSD1306 en el bus I2C (la normal es 0x3C)
const int DIRECCION_PANTALLA = 0x3C;

// Esta variable guarda si la pantalla contestó bien o no
bool pantalla_ok = false;

// ---------- Función: mandarle UN comando a la pantalla ----------
void enviar_comando(uint8_t comando) {
    // uint8_t es un número chico, de 0 a 255 (un "byte")
    // El primer byte (0x00) le avisa a la pantalla "lo que viene es un comando"
    uint8_t datos[2] = {0x00, comando};

    // Mandamos los 2 bytes por I2C a la dirección de la pantalla
    int resultado = i2c_write_blocking(i2c0, DIRECCION_PANTALLA, datos, 2, false);

    // Si el resultado es negativo, la pantalla no contestó (algo está mal conectado)
    if (resultado < 0) {
        pantalla_ok = false;
    }
}

// ---------- Función: preparar la pantalla ----------
void iniciar_pantalla() {
    pantalla_ok = true;   // partimos suponiendo que todo va bien; si falla algo, cambia a false

    // Lista de comandos que "despiertan" la pantalla de 128 x 64
    const uint8_t comandos[] = {
        0xAE,             // apagar pantalla mientras la configuramos
        0xD5, 0x80,       // velocidad del reloj interno
        0xA8, 0x3F,       // alto de la pantalla: 64 líneas
        0xD3, 0x00,       // sin desplazamiento vertical
        0x40,             // empezar a dibujar desde la primera línea
        0x8D, 0x14,       // encender la bomba de voltaje interna
        0x20, 0x00,       // modo de memoria horizontal
        0xA1,             // espejo horizontal (orientación normal)
        0xC8,             // espejo vertical (orientación normal)
        0xDA, 0x12,       // configuración de los pines de la pantalla
        0x81, 0xCF,       // brillo
        0xD9, 0xF1,       // tiempos de carga
        0xDB, 0x40,       // nivel de voltaje
        0xA4,             // mostrar lo que hay en memoria (pantalla normal)
        0xA6,             // colores normales (blanco sobre negro)
        0xAF              // encender la pantalla
    };
    const int cantidad = 25;   // cuántos comandos hay en la lista de arriba

    // Recorremos la lista y mandamos los comandos uno por uno
    for (int i = 0; i < cantidad; i++) {
        enviar_comando(comandos[i]);
    }
}

// ---------- Función: pintar TODA la pantalla de un mismo valor ----------
// valor 0xFF = todos los píxeles prendidos (blanco)
// valor 0x00 = todos los píxeles apagados (negro)
void llenar_pantalla(uint8_t valor) {
    enviar_comando(0x21);   // "te voy a decir qué columnas usar"
    enviar_comando(0);      // desde la columna 0
    enviar_comando(127);    // hasta la columna 127 (son 128 columnas)
    enviar_comando(0x22);   // "te voy a decir qué filas de 8 píxeles usar"
    enviar_comando(0);      // desde la fila 0
    enviar_comando(7);      // hasta la fila 7 (son 8 filas de 8 píxeles = 64)

    uint8_t datos[129];     // 1 byte de aviso + 128 bytes de píxeles (una fila completa)
    datos[0] = 0x40;        // 0x40 le avisa a la pantalla "lo que viene son píxeles"
    for (int i = 1; i < 129; i++) {
        datos[i] = valor;   // rellenamos los 128 píxeles de la fila con el valor
    }

    // Mandamos las 8 filas, una tras otra
    for (int fila = 0; fila < 8; fila++) {
        int resultado = i2c_write_blocking(i2c0, DIRECCION_PANTALLA, datos, 129, false);
        if (resultado < 0) {
            pantalla_ok = false;   // si falla el envío, anotamos que algo anda mal
        }
    }
}

int main() {
    // ---------- Preparar todo ----------
    stdio_init_all();      // activa el monitor serial
    sleep_ms(2000);        // esperamos 2 segundos para que alcance a abrirse

    adc_init();                        // enciende el lector analógico
    adc_gpio_init(PIN_PERILLA_H);      // GP26 trabaja como entrada analógica
    adc_gpio_init(PIN_PERILLA_V);      // GP27 trabaja como entrada analógica

    gpio_init(PIN_BOTON_TRAZO);                // preparamos el pin del botón de trazo
    gpio_set_dir(PIN_BOTON_TRAZO, GPIO_IN);    // lo dejamos como ENTRADA
    gpio_pull_up(PIN_BOTON_TRAZO);             // resistencia interna: sin apretar = 1

    gpio_init(PIN_BOTON_BORRAR);               // lo mismo para el botón de borrar
    gpio_set_dir(PIN_BOTON_BORRAR, GPIO_IN);
    gpio_pull_up(PIN_BOTON_BORRAR);

    i2c_init(i2c0, 400 * 1000);                // activa I2C a 400.000 bits por segundo
    gpio_set_function(PIN_SDA, GPIO_FUNC_I2C); // GP4 pasa a ser el cable de datos I2C
    gpio_set_function(PIN_SCL, GPIO_FUNC_I2C); // GP5 pasa a ser el cable de reloj I2C
    gpio_pull_up(PIN_SDA);                     // I2C necesita resistencias pull-up
    gpio_pull_up(PIN_SCL);

    iniciar_pantalla();                        // configuramos la pantalla

    // ---------- Prueba de arranque: toda la pantalla blanca por 1 segundo ----------
    llenar_pantalla(0xFF);     // pintamos todo de blanco
    sleep_ms(1000);            // lo dejamos 1 segundo para que alcances a verlo
    llenar_pantalla(0x00);     // y volvemos a dejar todo negro

    // ---------- Primer mensaje: ¿contestó la pantalla? ----------
    if (pantalla_ok) {
        printf("PANTALLA: responde bien por I2C\n");
    } else {
        printf("PANTALLA: NO responde. Revisa SDA (GP4), SCL (GP5), VCC y GND\n");
    }

    bool pantalla_blanca = false;   // recuerda si la pantalla está blanca ahora

    // ---------- Repetir para siempre ----------
    while (true) {
        adc_select_input(0);            // elegimos la entrada ADC 0 (GP26)
        int perilla_h = adc_read();     // leemos la perilla horizontal (0 a 4095)

        adc_select_input(1);            // elegimos la entrada ADC 1 (GP27)
        int perilla_v = adc_read();     // leemos la perilla vertical (0 a 4095)

        // gpio_get da 1 sin apretar y 0 apretado, por eso usamos "!" (lo contrario)
        bool trazo_apretado = !gpio_get(PIN_BOTON_TRAZO);
        bool borrar_apretado = !gpio_get(PIN_BOTON_BORRAR);

        // ¿Hay algún botón apretado?
        bool alguno_apretado = trazo_apretado || borrar_apretado;

        // Solo tocamos la pantalla cuando algo CAMBIA (así no la saturamos)
        if (alguno_apretado != pantalla_blanca) {
            if (alguno_apretado) {
                llenar_pantalla(0xFF);   // botón apretado: pantalla toda blanca
            } else {
                llenar_pantalla(0x00);   // botón suelto: pantalla toda negra
            }
            pantalla_blanca = alguno_apretado;   // anotamos cómo quedó
        }

        // Mostramos los valores en el monitor serial
        printf("H=%4d  V=%4d  trazo=%s  borrar=%s\n",
               perilla_h,
               perilla_v,
               trazo_apretado ? "APRETADO" : "suelto",
               borrar_apretado ? "APRETADO" : "suelto");

        sleep_ms(200);                  // esperamos un rato antes de repetir
    }
}
