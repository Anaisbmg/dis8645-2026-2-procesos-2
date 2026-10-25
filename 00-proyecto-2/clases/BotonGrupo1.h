// BotonGrupo1.h
// Este archivo define la clase Boton
// desarrollado por: 
// 
// Licencia 

#ifndef BOTON_H
#define BOTON_H

// agregamos el GPIO
// lo que hace es agregar la biblioteca del GPIO
// que deglosado es General Purpose Input/Output
#include "hardware/gpio.h"
#include "pico/stdlib.h"

// a continuación definimos la clase Boton
class Boton {

 // la hacemos public
 public:
 // definimos los atributos de Boton
 
 // IMPORTANTE
 // esta clase funciona solo con resistencia externa, 
 // es decir que revisar su circuito antes de usar
 // no nos responsabilizamos por daños en el hardware si no se usa correctamente
 
 // lugar que lee el Boton
 int pin;
 // detecta si Boton está siendo presionado
 bool presionado = false;
 // observa el estado anterior del Boton
 bool estadoAnterior = false;
 // valor asociado al boton funcionando como switch
 bool estadoSwitch = false;
 // detecta si se presionó el Boton dos veces
 bool estadoDoblePresionado = false;
 

 // para detectar tiempo se recomienda usar uint32_t
 // optimiza el uso de memoria

 // por cuanto tiempo se mantiene presionado
 uint32_t duracionPresionado = 0;
 // por cuanto tiempo se mantiene suelto
 uint32_t duracionSuelto = 0;
 // última vez que se leyó el estado del botón
 uint32_t ultimaLectura = 0;


 // definimos constructor
 // a qué numero de pin está conectado
 Boton(int pin);
 // definimos métodos
 // lee que Boton está conectado en el gpio
 void leer();
 // detecta un doble click
 void doblePresionado();
 // convierte el boton pulsador en switch
 void modoSwitch(estadoSwitch);
 
 // metodos especificos

 // realiza una lectura y cambia de modo
 // leer() + modoSwitch() = modoBorrar()
 void modoBorrar();
}; 

#endif
