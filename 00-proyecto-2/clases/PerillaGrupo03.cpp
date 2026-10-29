
#include "Perilla.h"
#include "hardware/adc.h"
#include <cstdlib>

// cuantas lecturas se promedian para quitar el ruido
static const int LECTURAS = 8;

// constructor
Perilla::Perilla(int nuevaPatita, int nuevaCantidadOpciones,
                 bool nuevoInvertir, int nuevoUmbral) {

  // guardar los valores
  patita = nuevaPatita;
  pin = nuevaPatita;
  cantidadOpciones = nuevaCantidadOpciones;
  invertir = nuevoInvertir;
  umbral = nuevoUmbral;

  // GP26 = canal 0, GP27 = canal 1, GP28 = canal 2
  canal = patita - 26;

  // la patita es entrada analogica
  adc_gpio_init(patita);

  // lectura inicial, para que la primera vuelta no cuente como movimiento
  // (adc_init() debe haberse ejecutado antes en el main)
  valor = muestrear();
}

// leer varias veces y entregar el promedio
int Perilla::muestrear() {

  // elegir el canal antes de leer
  adc_select_input(canal);

  int suma = 0;
  for (int i = 0; i < LECTURAS; i++) {
    suma += adc_read();
  }
  return suma / LECTURAS;
}

// opcion actual, con la cantidad indicada
int Perilla::posicion(int cantidad) {

  // dividir el recorrido (0 a 4095) en partes iguales, una por opcion
  int opcion = valor * cantidad / 4096;

  // si gira al reves, contar desde el otro extremo
  if (invertir) {
    opcion = cantidad - 1 - opcion;
  }

  // que nunca se salga del rango
  if (opcion < 0) {
    opcion = 0;
  }
  if (opcion > cantidad - 1) {
    opcion = cantidad - 1;
  }

  return opcion;
}

// leer la perilla y guardar el valor
int Perilla::leerValor() {
  valor = muestrear();
  return valor;
}

// leer la perilla y convertirla en opcion con la cantidad guardada
int Perilla::seleccionarOpcion() {
  leerValor();
  return posicion(cantidadOpciones);
}

// revisar si la perilla se movio (llamar una vez por vuelta)
void Perilla::leer() {

  // borrar el evento de la vuelta anterior
  movio = false;

  int lectura = muestrear();

  // solo es movimiento si el cambio supera el umbral
  if (abs(lectura - valor) > umbral) {
    valor = lectura;
    movio = true;
  }
}