#ifndef PERILLA_H
#define PERILLA_H

// esto lo agregamos para GPIO
// general purpose input output
#include "hardware/gpio.h"
// la perilla es mas sofisticada
// necesita ADC
// analog to digital conversion
#include "hardware/adc.h"


class Perilla {
  public:

// atributos
int posicion = 0;
int patita;

// constructor
Perilla (int nuevaPatita);

// metodos
void leer();

};


#endif