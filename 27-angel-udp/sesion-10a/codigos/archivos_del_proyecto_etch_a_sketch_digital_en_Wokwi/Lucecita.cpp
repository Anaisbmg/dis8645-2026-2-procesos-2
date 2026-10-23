// importar el archivo header
#include "Lucecita.h"



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

void Lucecita::rampear() {
  Lucecita::intensidad = Lucecita::intensidad + 1;

  if (Lucecita::intensidad > Lucecita::maxIntensidad) {
     Lucecita::intensidad = Lucecita::maxIntensidad;
  }
}

void Lucecita::iluminar() {

}

void Lucecita::morsePunto() {
  // prender
  gpio_put(Lucecita::patita, 1);
  // mantener prendido
  sleep_ms(Lucecita::duracionPunto);
  // apagar
  gpio_put(Lucecita::patita, 0);
  // pausa entre caracteres
  sleep_ms(Lucecita::duracionEntreCaracteres);
}

void Lucecita::morseRaya() {
  // prender
  gpio_put(Lucecita::patita, 1);
  // mantener prendido
  sleep_ms(Lucecita::duracionRaya);
  // apagar
  gpio_put(Lucecita::patita, 0);
  // pausa entre caracteres
  sleep_ms(Lucecita::duracionEntreCaracteres);
}


  // esperar 2 veces lo que dura el punto
  void Lucecita::finLetra() {
   sleep_ms(2 * Lucecita::duracionPunto);
  }

  // esperar 6 veces lo que dura el punto
  void Lucecita::finPalabra() {
    sleep_ms(6 * Lucecita::duracionPunto);
  }
