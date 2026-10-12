// Led.cpp
// implementaciones de la clase

// importar el archivo header
#include "Led.h"
#include "Pote.h"

// constructor
Led::Led(int nuevaConexionLed) {

  // guardar el valor
  // el doble : es para hacer un llamado dentro de un elemento
  conexionLed = nuevaConexionLed;

  
    // inicializar gpio
   gpio_init(conexionLed);
   // gpio es salida
   gpio_set_dir(conexionLed, GPIO_OUT);
}

void Led::encenderLed() {
 
 //el 1 corresponde a 3.3v
 // en IDE se describia HIGH
  gpio_put(conexionLed, 1); 

  //alteramos la variable que nos indica si un led enciende o no
  encendido = true;
}

void Led::apagarLed(){

  // 0 equivale a no haber señal
  // en IDE se describia LOW
  gpio_put(conexionLed, 0);

  //la variable encendido se vuelve falsa
  encendido = false;
}

void Led::oscilarLed(int tiempoEncendido, int tiempoApagado) {

//
uint32_t tiempoActual = to_ms_since_boot(get_absolute_time());

int tiempoDeEspera;
if(encendido == true) {
  tiempoDeEspera = tiempoEncendido;
 } else {
    tiempoDeEspera = tiempoApagado;
}

if (tiempoActual - ultimoCambio >= tiempoDeEspera) {
  gpio_put(conexionLed, !encendido);
    
    ultimoCambio = tiempoActual;
  }
}