// esto venia en wokwi
#include <stdio.h>
#include "pico/stdlib.h"

// incluir mis archivos
#include "Boton.h"
#include "Pote.h"
#include "Led.h"

int main() {

  stdio_init_all();

  // crear Boton que se llama botonNumero
  // con el constructor

  //manera poco optima y descartada para realizar cada boton
  // Boton botonUno(8);
  // Boton botonDos(9);
  //...
 // mejor optar por un array
 Boton botones[] = {Boton(8), Boton(9), Boton(10)};

  Pote miPrimerPote(26,0);
  Pote duracionEncendido(27,1);
  Pote duracionApagado(28,2);

 // lo mismo para los leds 

 
 Led lucesita[] = {Led(16), Led(17), Led(18)};
 //creamos una variable para identificar que lucesita esta activa en el array
 // inicia en -1 por que el primer valor del array corresponde a 0
 int lucesitaActiva = -1;

  while (true) {

       
    // lee todos los botones del array
    // & sirve para actualizar el estado del boton original
    for (auto& boton : botones) {
      boton.leer();
    }

    // definimos una nueva variable llamada i
    // que posee valores de 0 a 8
    // i++ es lo mismo que decir 
    // i = i + 1
    // al valor actual de i sumale uno
    for (int i = 0; i < 3; i++) {
    if (botones[i].presionado) {

      //revisa si el boton asociado al led es distinto
      // al que se esta presionando
      if (lucesitaActiva != i) {
      //antes de apagar la luz anterior, verifica que haya una luz encendida 
      if (lucesitaActiva != -1) {
        //apaga el led
        lucesita[lucesitaActiva].apagarLed();
      }
      // actualiza cual es el led que esta activo
      lucesitaActiva = i;
    }

    // si se presionan 2 botones se cancela el for del bucle
    break;
   
    }
   }


    //leemos mi primer pote
   miPrimerPote.leerPote();
   duracionEncendido.leerPote();
   duracionApagado.leerPote();
    // esto mantiene el led oscilando sin tener que mantener el boton
   if (lucesitaActiva != -1) {
    // se agrega un +2 para que la division nunca de 0
    int divisor = (miPrimerPote.valorPote / 84) + 2;
   
    if (divisor > 0) {
  
    // se realiza la matematica y guardamos el resultado
    // esto como parte de los buenos modales 
    int valor1 = duracionEncendido.valorPote / divisor;
    int valor2 = duracionApagado.valorPote / divisor;

    // 3. Imprimimos los valores resultantes en la consola
    // %d es el comodín para imprimir números enteros
    printf("Encendido: %d ms - Apagado: %d ms\n", valor1, valor2);

    // 4. Inyectamos las variables limpias en tu método
    lucesita[lucesitaActiva].oscilarLed(valor1, valor2);
    }
   }
   sleep_ms(20);
  }
}

