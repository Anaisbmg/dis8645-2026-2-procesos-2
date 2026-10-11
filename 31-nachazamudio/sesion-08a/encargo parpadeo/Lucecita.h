#ifndef LUCECITA_H
#define LUCECITA_H

// esto lo agregamos para GPIO
// general purpose input output
#include "hardware/gpio.h"
//se añade esto para que funcione el sleep
#include "pico/stdlib.h"

class Lucecita {
  public:

  // atributos
  int patita;
  int prendida = false;

  // constructor
  Lucecita(int nuevaPatita);

  // metodos
  void prender();
  void apagar();

  //agregamos un método más de parpadeo
  //con un parámetro de frecuencia
  void parpadear(int frecuencia);

};


#endif