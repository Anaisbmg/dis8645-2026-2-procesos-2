// Vamos a definir la clase Perilla, que sirve para las dos perillas
// del proyecto:
//  - Perilla 1: velocidad de bajada de las luces.
//  - Perilla 2: moverse entre los 4 caminos del juego.
// Para el grupo 06:
//  - Perilla 1: velocidad de movimiento mapa
//  - Perilla 2: selección de personaje (4 opciones)
// 

// Esqueleto base
#ifndef PERILLA_H
#define PERILLA_H

#include "hardware/gpio.h"// Biblioteca que nos deja interactuar con los pines físicos de la raspberry.
#include "hardware/adc.h" // la perilla es mas sofisticada
                          // necesita ADC
                          // analog to digital conversion


// Aquí empieza la clase Perilla
class Perilla {

  public: // nada privade 


    // ATRIBUTOS 
    // Los atributos son lo que cada perilla necesita saber.

    int posicion = 0; // 0 a 4095
    int patita;  // Guarda el pin (la patita) de la raspberry donde está conectada la perilla.
    int ultimoPaso = -1;    // para recordar el paso anterior (histeresis)


    // CONSTRUCTOR 
    Perilla(int nuevaPatita);


    // MÉTODOS 
    // Acciones que sabe hacer la perilla.
    void leer();
    float porcentaje();
    int paso(int cantidadPasos);

};

#endif
