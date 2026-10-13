#ifndef POTE_H
#define POTE_H

// esto lo agregamos para GPIO
// general purpose input output
#include "hardware/adc.h"

class Pote {

  public:

  //atributos -----
  int conexion; //en que GPio se encuentra conectado
  uint16_t valorPote; //valor que se obtiene de la lectura del pote (solo es positivo)
  // ademas se indica que inicia en 0 para identificar si no posee lectura
  int pinADC; // corresponde al adc que convierte la señal 

  //constructor -----
  Pote(int nuevaConexion, int nuevoPinADC);

  //metodos -----
  void leerPote();
  };

#endif // esto sumado a la primera linea sirven para que solo sea llamado una vez y no caiga en un bucle