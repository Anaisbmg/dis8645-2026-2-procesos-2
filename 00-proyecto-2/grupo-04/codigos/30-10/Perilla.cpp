// Perilla.cpp
// implementaciones de la clase

#include "Perilla.h"
#include <stdlib.h>

// constructor
Perilla::Perilla(int nuevaPatita) {

  Perilla::patita = nuevaPatita;
  Perilla::canal = nuevaPatita - 26;

  // iniciar el ADC y dejar la patita como entrada analogica
  adc_init();
  adc_gpio_init(Perilla::patita);

  Perilla::valor = Perilla::muestrear();
}

// lee el potenciometro (promedio de 8 lecturas para quitar ruido)
int Perilla::muestrear() {
  adc_select_input(Perilla::canal);

  uint32_t suma = 0;
  for (int i = 0; i < 8; i++) {
    suma += adc_read();
  }
  return suma / 8;
}

// en que tramo (0 a cantidad-1) esta la perilla
// el recorrido se divide en partes iguales: una por opcion
int Perilla::posicion(int cantidad) {
  int v = Perilla::invertir ? 4095 - Perilla::valor : Perilla::valor;
  int p = v * cantidad / 4096;

  if (p > cantidad - 1) {
    p = cantidad - 1;
  }
  if (p < 0) {
    p = 0;
  }
  return p;
}

void Perilla::leer() {

  Perilla::movio = false;

  // solo cuenta si se movio de verdad (evita que tiemble en el borde de un tramo)
  int lectura = Perilla::muestrear();
  if (abs(lectura - Perilla::valor) > Perilla::umbral) {
    Perilla::valor = lectura;
    Perilla::movio = true;
  }
}