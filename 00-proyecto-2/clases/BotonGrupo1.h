#ifndef BOTON_H
#define BOTON_H

// agregamos el GPIO
// lo que hace es agregar la biblioteca del GPIO
// que deglosado es General Purpose Input/Output
#inlude "hardware/gpio.h"

// a continuación definimos la clase Boton
class Boton
{

  // la hacemos public
public:
  // definimos los atributos de Boton

  // lugar que lee el Boton
  int pin;

  // detecta si Boton está siendo presionado
  bool presionado = false;

  // por cuanto tiempo se mantiene presionado
  int duracionPresionado = 0;

  // definimos constructor

  // a qué numero de pin está conectado
  Boton(int pin)

      // definimos métodos

      void leer();
  void presionar();
  void soltar();
}

#endif
