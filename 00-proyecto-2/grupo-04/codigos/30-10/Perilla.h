#ifndef PERILLA_H
#define PERILLA_H

#include "pico/stdlib.h"
#include "hardware/adc.h"


// Perilla.h
// declaraciones de la clase Perilla
// (potenciometro leido con el ADC del Pico)
// el recorrido del potenciometro se reparte en tramos iguales,
// un tramo por cada opcion (cada caracter tiene su espacio)


class Perilla {

  // todo publico
  public:

  // atributos
  int patita;                   // GP26, GP27 o GP28 (las unicas con ADC)
  int canal;                    // 0, 1 o 2
  int valor = 0;                // 0 a 4095
  bool movio = false;           // true solo en la vuelta donde se movio
  int umbral = 20;              // cuanto debe moverse para contar como movimiento
  bool invertir = false;        // cambiar a true si queda al reves


  // constructor
  Perilla(int nuevaPatita);

  // metodos
  void leer();
  int posicion(int cantidad);
  int muestrear();

};

#endif