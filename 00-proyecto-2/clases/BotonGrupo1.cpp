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


// definimos el método leer
// definimos que la gran mayoria de lecturas ocurran en este metodo
// de esta manera escondemos la complejidad de la clase Boton
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
   // esto nos protege de tener miles de lecturas al mantener presionado el boton
   if (nuevoPresionado != presionado) {
   // presionado toma el valor de nuevoPresionado   
   // actualizamos el valor oficil basicamente
     presionado = nuevoPresionado;  
    }
  }

 // creamos una varible que nos pueda servir para detectar doble click
 // se aloja aca para esconder la complejidad en .h
 bool esperandoDoblePresionado = false;
 // si presionado es verdadero
 if (presionado) {
   // y si esparamos un doble click
   // y el tiempo transcurrido desde la última lectura es menor a tiempoDoblePresionado
   // entonces se detecta un doble click
   if (esperandoDoblePresionado) {
     if (tiempoActual - ultimaLectura < tiempoDoblePresionado) {
       estadoDoblePresionado = true;
       esperandoDoblePresionado = false;
      }
     }
     // si no esperandoDoblePresionado se actualiza a verdadero 
     // para esperar el segundo click
     }
     else {
    ultimaLectura = tiempoActual;
    esperandoDoblePresionado = true;
   }
   // definimos la ventana de tiempo para detectar doble click
   // si esperandoDoblePresionado es verdadero y el tiempo transcurrido
   //desde la última lectura es mayor a tiempoDoblePresionado
   // esperandoDoblePresionado se actualiza a falso
   // && es un operador lógico que significa y
   // osea que si 2 elementos son verdaderos
   // se ejecuta la instrucción
   if (esperandoDoblePresionado && (tiempoActual - ultimaLectura > tiempoDoblePresionado)) {
     esperandoDoblePresionado = false;
   }

   if (presionado) {
    // calculamos la duración que se mantuvo presionado
   duracionPresionado = tiempoActual - ultimaLectura;
   // reiniciamos la duración de suelto
   duracionSuelto = 0;
   // si presionado es falso 
     } 
     else {
   // calculamos la duración que se mantuvo suelto
   duracionSuelto = tiempoActual - ultimaLectura;
   // reiniciamos la duración de presionado
   duracionPresionado = 0; 
  }

 // actualizamos el estado anterior
 estadoAnterior = nuevoPresionado;
}


// utilizamos bool para detectar doble click
// esto facilita su uso en el main.cpp
// solo leemos el estado de doble click y si es verdadero
bool Boton::doblePresionado(tiempoDoblePresionado) {
 // si estadoDoblePresionado es verdadero 
 if (estadoDoblePresionado) {
   // reiniciamos estadoDoblePresionado a falso
   // para no leer de nuevo el estado de doble click
    estadoDoblePresionado = false;
    // devolvemos verdadero
    // return es una instrucción que devuelve un valor
    // y termina la accion de la funcion
     return true;
  }
  return false;
}

// metodo que convierte el boton pulsador en switch
void Boton::mantenerPresionado() {
 // si presiono el boton y antes no estaba presionado
 // se inicia el modo switch
 // que es lo mismo que decir
 // que se mantiene presionado el boton

 // si presiono el boton y antes estaba presionado
 // se desactiva el modo switch
 // que es lo mismo que decir
 // que se suelta el boton

  if (presionado && !presionadoProcesado) {
    // cambiamos el estado de estadoMantenerPresionado
    estadoMantenerPresionado = !estadoMantenerPresionado;
    presionadoProcesado = true;  
  } 
  else if (!presionado) {
    presionadoProcesado = false;
  }
}

//
void Boton::modoBorrar() {
  estadoDoblePresionado = false;
}