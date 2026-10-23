// Boton.cpp
// implementaciones de la clase

// importar el archivo header
#include "Boton.h"

// constructor
Boton::Boton(int nuevaPatita) {

  // guardar el valor
  Boton::patita = nuevaPatita;

   // inicializar patita
  gpio_init(Boton::patita);
  // la patita es entrada
  gpio_set_dir(Boton::patita, GPIO_IN);
}

void Boton::leer() {
    Boton::presionadoAnterior = Boton::presionado;
    // actualiza el estado actual del boton
    Boton::presionado = gpio_get(Boton::patita);

    // si antes no estaba presionado
    // y ahora si esta presionado
    if ( Boton::presionadoAnterior == false &&
        Boton::presionado == true) {
           Boton::recienPresionado = true;
           printf("me presionaron\n");
        }
    else {
      Boton::recienPresionado = false;
    }

}

// metodos
void Boton::presionar() {
  Boton::presionado = true;
  // queda pendiente calcular
  // cuanto rato lleva presionado
}
  
void Boton::soltar() {
   Boton::presionado = false;
   Boton::duracionPresionado = 0;
}