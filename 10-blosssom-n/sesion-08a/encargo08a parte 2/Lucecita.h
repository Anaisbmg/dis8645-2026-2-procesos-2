#ifndef LUCECITA_H
#define LUCECITA_H

// esto lo agregamos para GPIO
// general purpose input output
#include "hardware/gpio.h"


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

  // para parpadear le damos un tiempo
  // asi podemos cambiar que tan rapido va
  void parpadear(int tiempo);


};


#endif