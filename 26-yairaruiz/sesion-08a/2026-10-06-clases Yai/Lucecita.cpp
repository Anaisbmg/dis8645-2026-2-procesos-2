// importar el archivo header
#include "Lucecita.h"
#include "pico/stdlib.h"   
#include "pico/time.h"     


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

void Lucecita::parpadear(int periodo_ms) {
    unsigned long ahora = to_ms_since_boot(get_absolute_time());

    // cada medio período cambia de estado
    if (ahora - ultimo_cambio >= (unsigned long)(periodo_ms / 2)) {
        if (estado_parpadeo) {
            apagar();
        } else {
            prender();
        }
        estado_parpadeo = !estado_parpadeo;
        ultimo_cambio = ahora;
    }
}