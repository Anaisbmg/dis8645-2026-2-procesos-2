#ifndef LUCECITA_H
#define LUCECITA_H

// esto lo agregamos para GPIO
// general purpose input output
#include "hardware/gpio.h"
// este es para sleep_ms
#include "pico/stdlib.h"
// agregamos PWM
// #include "hardware/pwm.h"

class Lucecita {
  public:

  // atributos
  int patita;
  int prendida = false;
  int intensidad = 0;

  // parametros del morse
  int duracionPunto = 200;
  int duracionRaya = 1000;
  int duracionEntreCaracteres = 500;
 
  // pausa por complejidad
  int minIntensidad = 0;
  int maxIntensidad = 1024;


  // constructor
  Lucecita(int nuevaPatita);

  // metodos
  void prender();
  void apagar();

  void iluminar();

  // ir de minimo a maximo
  // PAUSA PQ COMPLEJIDAD
  void rampear();

  void morsePunto();

  void morseRaya();

  void finLetra();

  void finPalabra();


};


#endif