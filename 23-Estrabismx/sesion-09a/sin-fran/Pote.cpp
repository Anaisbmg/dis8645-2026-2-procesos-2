// Pote.cpp
// implementaciones de la clase

// importar el archivo header
#include "Pote.h"

// constructor
Pote::Pote(int nuevaConexion, int nuevoPinADC) {

  // guardar el valor
  // el doble : es para hacer un llamado dentro de un elemento
  conexion = nuevaConexion;
  pinADC = nuevoPinADC;
    // inicializar ADC
    // Analog to Digital Converte
    adc_init();

    //preparar GPio para entrada analoga
    adc_gpio_init(conexion);

}

void Pote::leerPote() {

  //seleccionar canal del ADC
    adc_select_input(pinADC);

    // leer un pote
    Pote::valorPote = adc_read(); 
}