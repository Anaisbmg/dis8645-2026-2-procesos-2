#ifndef PANTALLA_H
#define PANTALLA_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"


// Pantalla.h
// declaraciones de la clase Pantalla
// (LCD 20x4 con modulo I2C PCF8574)


class Pantalla {

  // todo publico
  public:

  // atributos
  i2c_inst_t* bus;              // i2c0 o i2c1
  int patitaSda;
  int patitaScl;
  uint8_t direccion;            // normalmente 0x27
  int columnas = 20;
  int filas = 4;


  // constructor
  Pantalla(i2c_inst_t* nuevoBus, int nuevaSda, int nuevaScl,
           uint8_t nuevaDireccion = 0x27);

  // metodos
  void limpiar();
  void moverCursor(int fila, int columna);
  void escribirLinea(int fila, const char* texto);
  void mostrarCursor(bool visible);

  // metodos de bajo nivel (hablar con el LCD)
  void iniciar();
  void comando(uint8_t valor);
  void dato(uint8_t valor);
  void enviarByte(uint8_t valor, bool esDato);
  void enviarMitad(uint8_t mitad, bool esDato);
  void pulsarEnable(uint8_t valor);
  void enviarExpansor(uint8_t valor);

};

#endif