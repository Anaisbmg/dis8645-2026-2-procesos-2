#include "Perilla.h"
#include "hardware/adc.h"

// CONSTRUCTOR
// Se ejecuta cuando creamos un objeto Perilla.
// Guarda el GPIO recibido.
// Todavia no lee ni configura el hardware.

Perilla::Perilla(unsigned int pinADC) {
    pin = pinADC;
    lectura = 0;
}

// INICIAR
// Prepara el GPIO para recibir una senal analogica.
// En esta primera version usaremos
// exclusivamente GP26 y GP27.
// El ADC compartido se inicializa en main.cpp.

void Perilla::iniciar() {
    adc_gpio_init(pin);
}

// LEER
// La Pico comparte un ADC entre varias entradas.
// Antes de leer, seleccionamos la entrada
// correspondiente a esta perilla:
// GP26 corresponde a la entrada ADC 0.
// GP27 corresponde a la entrada ADC 1.
// Por eso restamos 26 al numero del GPIO.

uint16_t Perilla::leer() {
    adc_select_input(pin - 26);

    lectura = adc_read();

    return lectura;
}

// CONVERTIR
// Usamos la lectura que guardo leer().
// Aqui no realizamos otra lectura.
// Ejemplo para el eje X:
// Lectura 0    es posicion 0.
// Lectura 4095 es posicion 319.
// Asi el recorrido completo de la perilla
// corresponde al recorrido completo del eje.

int Perilla::convertir(int minimo, int maximo) {
    int32_t recorrido = maximo - minimo;

    return minimo +
           (static_cast<int32_t>(lectura) * recorrido) / 4095;
}
