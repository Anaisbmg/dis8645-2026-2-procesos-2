// importar el archivo header
#include "Perilla.h"

// este prefijo
// Perilla::
// significa dentro de la clase Perilla

// constructor
Perilla::Perilla (int nuevaPatita) {

  // guardar el valor
  Perilla::patita = nuevaPatita;

  
  adc_init();

  // inicializar patita
  adc_gpio_init(Perilla::patita);


}

// metodos
void Perilla::leer() {

 
  adc_select_input(Perilla::patita - 26);

  // leer con ADC
  // y guardar en posicion
  Perilla::posicion = adc_read(); 

}
