// main.cpp (BOTONES + PERILLAS)
// Junta los dos botones y las dos perillas en los dos momentos
// del juego: el menú y jugando.
// Todavía no hay matriz LED ni sonido: por ahora todo se
// muestra en el monitor serial para comprobar que funciona.

#include <stdio.h>
#include "pico/stdlib.h"
#include "Boton.h"
#include "Perilla.h"

// Creamos los dos botones y las dos perillas diciendo en qué pin
// está cada uno. Los constructores ya dejan los pines listos.
Boton boton1(7);        // navegar entre niveles
Boton boton2(8);        // seleccionar nivel / atrapar la luz
Perilla perilla1(26);   // velocidad de las luces
Perilla perilla2(27);   // los 4 caminos

// Los dos momentos del programa. El programa siempre está en uno solo.
//  - menu: la persona escoge el nivel.
//  - jugando: las luces bajan y la persona las atrapa.
enum Momento { menu, jugando };

int main() {

  // Activa la comunicación por USB para poder imprimir mensajes.
  stdio_init_all();

  // Pausa SOLO en esta prueba, para darle tiempo al monitor serial.
  sleep_ms(2000);

  // Guarda en qué momento está el programa. Empieza en el menú.
  Momento momento = menu;

  // Guarda el nivel que se está mostrando o jugando (1, 2 o 3).
  int nivel = 1;

  // Guarda la hora en que empezó el nivel que se está jugando.
  // Sirve para medir los 2:00 minutos.
  uint32_t horaInicioNivel = 0;

  // Duración de cada nivel en milisegundos: 2 minutos = 120000 ms.
  // Para probar más rápido en Wokwi se puede bajar a 10000 (10 s).
  uint32_t duracionNivel = 120000;

  // Guardan lo último que se imprimió, para no llenar el monitor
  // de mensajes repetidos.
  int ultimoPorcentaje = -100;
  int ultimoCamino = -1;

  printf("Menu listo. Nivel actual: %d\n", nivel);

  // Ciclo principal: se repite para siempre, sin pausas.
  while (true) {

    // Leemos TODO en cada vuelta, sin importar el momento.
    // Así nunca se pierde una pulsación ni una lectura.
    boton1.leer();
    boton2.leer();
    perilla1.leer();
    perilla2.leer();

    // Preguntamos las pulsaciones UNA sola vez por vuelta, porque
    // huboPulsacion() borra el aviso después de entregarlo.
    bool pulsoBoton1 = boton1.huboPulsacion();
    bool pulsoBoton2 = boton2.huboPulsacion();

    // ========================================================
    // MOMENTO: MENÚ
    // ========================================================
    if (momento == menu) {

      // Botón 1: pasa al siguiente nivel (1 -> 2 -> 3 -> 1).
      if (pulsoBoton1) {
        nivel = nivel + 1;
        if (nivel > 3) {
          nivel = 1;
        }
        printf("Navegando. Nivel actual: %d\n", nivel);
      }

      // Botón 2: selecciona el nivel y empieza el juego.
      if (pulsoBoton2) {
        printf("Nivel %d SELECCIONADO. Empieza el juego\n", nivel);

        // Pasamos al momento "jugando" y anotamos la hora de inicio.
        momento = jugando;
        horaInicioNivel = to_ms_since_boot(get_absolute_time());

        // Reiniciamos lo último impreso para que se muestren
        // los valores de las perillas apenas empiece el juego.
        ultimoPorcentaje = -100;
        ultimoCamino = -1;
      }
    }

    // ========================================================
    // MOMENTO: JUGANDO
    // ========================================================
    else if (momento == jugando) {

      // Perilla 1: velocidad de bajada, en porcentaje (0 a 100).
      // Más adelante este número decidirá qué tan rápido bajan las luces.
      int porcentajeActual = (int)perilla1.porcentaje();

      // Solo imprimimos si cambió 3 puntos o más.
      if (porcentajeActual - ultimoPorcentaje >= 3 ||
          ultimoPorcentaje - porcentajeActual >= 3) {
        ultimoPorcentaje = porcentajeActual;
        printf("Velocidad: %d%%\n", porcentajeActual);
      }

      // Perilla 2: camino donde está el LED de la jugadora (1 a 4).
      int caminoActual = perilla2.paso(4);

      // Solo imprimimos cuando cambia de camino.
      if (caminoActual != ultimoCamino) {
        ultimoCamino = caminoActual;
        printf("LED en el camino: %d\n", caminoActual);
      }

      // Botón 2: la jugadora intenta atrapar la luz.
      // El botón solo avisa. Más adelante, aquí se revisará si había
      // una luz en la zona de captura y si estaba en este camino.
      if (pulsoBoton2) {
        printf("Intento de atrapar en el camino %d\n", caminoActual);
      }

      // Revisamos si ya pasaron los 2:00 minutos del nivel.
      uint32_t ahora = to_ms_since_boot(get_absolute_time());
      if (ahora - horaInicioNivel >= duracionNivel) {

        if (nivel < 3) {
          // Todavía quedan niveles: pasa al siguiente.
          nivel = nivel + 1;
          horaInicioNivel = ahora;
          printf("Nivel superado. Empieza el nivel %d\n", nivel);
        } else {
          // Terminó el nivel 3: se acaba el juego y vuelve al menú.
          nivel = 1;
          momento = menu;
          printf("Fin del juego. Menu listo. Nivel actual: %d\n", nivel);
        }
      }
    }
  }
}
