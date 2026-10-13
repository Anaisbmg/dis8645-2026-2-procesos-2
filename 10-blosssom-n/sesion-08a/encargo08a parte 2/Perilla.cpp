// importar el archivo header
#include "Perilla.h"

// este prefijo
// Perilla::
// significa dentro de la clase Perilla

// constructor
Perilla::Perilla (int nuevaPatita) {

  // guardar el valor
  Perilla::patita = nuevaPatita;

  // preparar la entrada analoga
  // duda para el futuro
  // es necesario para cada perilla?
  // da lo mismo si cada perilla lo hace?
  // o quizas horror sera un problema?
  adc_init();

  // inicializar patita
  adc_gpio_init(Perilla::patita);


}

// metodos
void Perilla::leer() {

  // seleccionar canal del ADC
  // eso se hace con la patita
  // ese - 26 es porque
  // patita 26 va a ADC0
  // 27 va a ADC1 ec revisar
  adc_select_input(Perilla::patita - 26);

  // leer con ADC
  // y guardar en posicion
  Perilla::posicion = adc_read(); 

}
