// Matriz.cpp
// implementaciones de la clase

// importar el archivo header
#include "Matriz.h"

// Esto lo agregamos para leer la velocidad del reloj de la raspberry.
// Hace falta para calcular a qué ritmo manda datos el PIO.
#include "hardware/clocks.h"

// ============================================================

// PROGRAMA DEL PIO
// Estas 4 instrucciones son el programa que le enseña al PIO cómo
// mandar la señal a los LEDs WS2812 con los tiempos exactos que
// ellos piden. Normalmente viven en un archivo .pio, pero como
// Wokwi no lo acepta, las escribimos ya traducidas a números.
// No se modifican.
static const uint16_t ws2812_instrucciones[] = {
  0x6221,
  0x1123,
  0x1400,
  0xa442
};

// Esta ficha le cuenta al PIO dónde está el programa y cuántas
// instrucciones tiene (4). El -1 significa "ponlo donde haya espacio".
static const struct pio_program ws2812_programa = {
  ws2812_instrucciones,
  4,
  -1
};

// ============================================================

// constructor
Matriz::Matriz(int nuevaPatita) {

  // guardar el valor
  Matriz::patita = nuevaPatita;

  // Escogemos el PIO 0 y su máquina número 0.
  Matriz::pio = pio0;
  Matriz::maquina = 0;

  // Cargamos el programa en el PIO y anotamos dónde quedó guardado.
  int offset = pio_add_program(Matriz::pio, &ws2812_programa);

  // Le decimos al PIO que este pin va a ser controlado por él.
  pio_gpio_init(Matriz::pio, Matriz::patita);

  // Dice que el pin es de SALIDA: la raspberry escribe, no lee.
  pio_sm_set_consecutive_pindirs(Matriz::pio, Matriz::maquina,
                                 Matriz::patita, 1, true);

  // Creamos la configuración de la máquina del PIO.
  pio_sm_config configuracion = pio_get_default_sm_config();

  // Le decimos en qué instrucciones empieza y termina el programa
  // para que lo repita en ciclo (de la 0 a la 3).
  sm_config_set_wrap(&configuracion, offset + 0, offset + 3);

  // El programa usa 1 bit extra para subir y bajar el pin.
  sm_config_set_sideset(&configuracion, 1, false, false);
  sm_config_set_sideset_pins(&configuracion, Matriz::patita);

  // Cada LED recibe 24 bits (8 de verde, 8 de rojo y 8 de azul).
  sm_config_set_out_shift(&configuracion, false, true, 24);

  // Juntamos las dos filas de espera del PIO para mandar más datos
  // seguidos sin que se atasque.
  sm_config_set_fifo_join(&configuracion, PIO_FIFO_JOIN_TX);

  // Los WS2812B piden 800000 bits por segundo, y cada bit gasta
  // 10 ciclos del programa. Con eso calculamos qué tan lento debe
  // ir el PIO respecto al reloj de la raspberry.
  float divisor = clock_get_hz(clk_sys) / (800000.0f * 10.0f);
  sm_config_set_clkdiv(&configuracion, divisor);

  // Dejamos todo cargado y encendemos la máquina del PIO.
  pio_sm_init(Matriz::pio, Matriz::maquina, offset, &configuracion);
  pio_sm_set_enabled(Matriz::pio, Matriz::maquina, true);

  // partir apagada
  Matriz::limpiar();
  Matriz::mostrar();
}

// metodos

void Matriz::limpiar() {

  // Recorremos los 64 LEDs del dibujo y los dejamos en negro (apagados).
  for (int i = 0; i < 64; i++) {
    Matriz::pixeles[i] = NEGRO;
  }
}

void Matriz::pintarPixel(int fila, int columna, uint32_t color) {

  // Si la fila o la columna se salen de la matriz (menores a 0 o
  // mayores a 7), no hacemos nada, para no escribir fuera del dibujo.
  if (fila < 0 || fila > 7 || columna < 0 || columna > 7) {
    return;
  }

  // Guardamos el color en la posición de esa fila y columna.
  Matriz::pixeles[fila * 8 + columna] = color;
}

void Matriz::pintarCamino(int camino, int fila, uint32_t color) {

  // Si el camino no está entre 1 y 4, no hacemos nada.
  if (camino < 1 || camino > 4) {
    return;
  }

  // Cada camino ocupa 2 columnas. El camino 1 empieza en la columna 0,
  // el 2 en la 2, el 3 en la 4 y el 4 en la 6.
  int primeraColumna = (camino - 1) * 2;

  // Pintamos las dos columnas del camino en esa fila.
  Matriz::pintarPixel(fila, primeraColumna, color);
  Matriz::pintarPixel(fila, primeraColumna + 1, color);
}

void Matriz::mostrar() {

  // Recorremos los LEDs en el orden en que están cableados en la
  // tira: el 0 es el primero que recibe la señal, y así hasta el 63.
  for (int i = 0; i < 64; i++) {

    // Calculamos en qué fila y columna del dibujo está este LED.
    int fila = i / 8;
    int columna = i % 8;

    // Si la matriz es serpentina, en las filas impares el orden va
    // al revés, y entonces damos vuelta la columna.
    if (Matriz::serpentina && (fila % 2 == 1)) {
      columna = 7 - columna;
    }

    // Tomamos el color de ese LED desde el dibujo.
    uint32_t color = Matriz::pixeles[fila * 8 + columna];

    // Separamos el color en sus tres partes: rojo, verde y azul.
    uint32_t rojo  = (color >> 16) & 0xFF;
    uint32_t verde = (color >> 8) & 0xFF;
    uint32_t azul  = color & 0xFF;

    // Aplicamos el brillo: con brillo 20, cada color queda al 20%.
    rojo  = rojo  * Matriz::brillo / 100;
    verde = verde * Matriz::brillo / 100;
    azul  = azul  * Matriz::brillo / 100;

    // Los WS2812 piden los colores en orden VERDE, ROJO, AZUL.
    // El corrimiento final de 8 es porque el PIO lee desde la izquierda.
    uint32_t palabra = (verde << 24) | (rojo << 16) | (azul << 8);

    // Enviamos el color al PIO.
    pio_sm_put_blocking(Matriz::pio, Matriz::maquina, palabra);
  }
}
