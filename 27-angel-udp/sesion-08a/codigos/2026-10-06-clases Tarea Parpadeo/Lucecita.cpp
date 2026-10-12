// importar el archivo header
#include "Lucecita.h"
#include "pico/stdlib.h"


// constructor
Lucecita::Lucecita(int nuevaPatita) {
  

  // guardar el valor
  Lucecita::patita = nuevaPatita;

  // inicializar patita
  gpio_init(Lucecita::patita);

  // la patita es salida
  gpio_set_dir(Lucecita::patita, GPIO_OUT);
 
  // partir apagada
  Lucecita::apagar();

}

// metodos
void Lucecita::prender() {


  // hacer true la variable interna
  Lucecita::prendida = true;

  // usar la variable para prender
  // con gpio_put que es de raspico sdk
  gpio_put(Lucecita::patita, true);


}

void Lucecita::apagar() {

   // hacer false la variable interna
  Lucecita::prendida = false;

  // usar la variable para prender
  // con gpio_put que es de raspico sdk
  gpio_put(Lucecita::patita, false);
}

// nuevo metodo para parpadear
void Lucecita::parpadear(int tiempo) {

  // prender luz
  Lucecita::prender();

  // esperar el tiempo indicado
  sleep_ms(tiempo);

  // apagar luz
  Lucecita::apagar();

  // esperar nuevamente
  sleep_ms(tiempo);
}