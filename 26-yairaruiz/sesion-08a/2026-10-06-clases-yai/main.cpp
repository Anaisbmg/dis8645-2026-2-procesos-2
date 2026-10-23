// hay 3 elementos
// lucecita
// perilla
// pulsador

// lucecita necesita R de 220
// perilla necesita nada
// pulsador necesita R de 10k

// entradas
// o sensores
// perilla - posicion rotacional / giro
// pulsador - si o no hay presion

// salidas
// o actuadores
// lucecita



// pulsador: prender y apagar todo
// potenciometro: frecuencia de parpadeo

// lucecita: prender y apagarse
// segun lo que diga boton y perilla

// por lo tanto
// boton tiene dos estados
// prendido y apagado

// perilla va a tener
// una posicion que va a ser
// usada por el sistema
// para impactar en parpadeo lucecita



#include <stdio.h>
#include "pico/stdlib.h"

#include "Boton.h"
#include "Perilla.h"
#include "Lucecita.h"

int main() {
  stdio_init_all();


  // instanciar Boton llamado pulsador
  // a partir de la clase Boton
  // con el parametro
  Boton pulsador(7);

  // lo mismo pero con perilla
  Perilla parpadeo(26);

  Lucecita luz(6);


  while (true) {
    
    pulsador.leer();
    parpadeo.leer();

    if (pulsador.presionado) {
      // mapear 0..4095 -> 200ms..2000ms
      // 200 ms = parpadeo rápido, 2000 ms = parpadeo lento
      int periodo = 200 + (parpadeo.posicion * 1800) / 4095;

      luz.parpadear(periodo);  
    } else {
      luz.apagar();
      // resetear el estado interno del parpadeo para que arranque limpio
      luz.estado_parpadeo = false;
    }

    printf("posicion perilla=%d\n", parpadeo.posicion);
    sleep_ms(10);   // loop rápido, ya no 250 ms
  }
  }
