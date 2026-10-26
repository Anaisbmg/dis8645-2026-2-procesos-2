//BotonGrupo1.cpp
#include "BotonGrupo1.h"

//constructor
Boton::Boton(int nuevoPin) {
  pin = nuevoPin;
  
  // inicializamos el pin como entrada
  gpio_init(pin);
  // configuramos el pin como entrada
  gpio_set_dir(pin, GPIO_IN);
}

void Boton::leer(){
 // leemos el tiempo transcurrido desde que se encendió el microcontrolador
 // tiempoActual almacena el tiempo en milisegundos
 uint32_t tiempoActual = to_ms_since_boot(get_absolute_time());
 
 // se crea una variable momentanea que lee el estado del pin
 // si recibe voltaje, presionado = true / 1
 bool nuevoPresionado = gpio_get(pin);

 // si el estado anterior es diferente del actual
 // != significa diferente
 if (nuevoPresionado != estadoAnterior) {
   // si lo anterior es verdad
   // actualizamos la última lectura
   // ahora ultimaLectura es igual al tiempo desde que se encendió el microcontrolador
   ultimaLectura = tiempoActual;  
 }
  
 // ahora vamos a filtrar el ruido
 // si el tiempo transcurrido desde la última lectura es mayor a 50 milisegundos
 if ((tiempoActual - ultimaLectura) > 50) {
 // si la lectura actual es diferente de presionado
 if (nuevoPresionado != presionado) {
 // presionado toma el valor de nuevoPresionado   
 presionado = nuevoPresionado;  
 }
}

// actualizamos el estado anterior
estadoAnterior = presionado;

// si presionado es verdadero
// calculamos la duración que se ha mantenido presionado
if (presionado) {   
 duracionPresionado = tiempoActual - ultimoTiempoLectura;
 // reiniciamos la duración de suelto
 duracionSuelto = 0;
 // si presionado es falso 
 } else {
 // calculamos la duración que se mantuvo suelto
 duracionSuelto = tiempoActual - ultimoTiempoLectura;
 // reiniciamos la duración de presionado
 duracionPresionado = 0; 
}
}



void Boton::doblePresionado() {
 // si se presiono el boton, y la duracion es mayor a 50 ms y menor a 500 ms
 // entonces se considera un doble click
 if (presionado && duracionPresionado > 50 && duracionPresionado < 500) {
  estadoDoblePresionado = true;
 } else { 
}

 
}