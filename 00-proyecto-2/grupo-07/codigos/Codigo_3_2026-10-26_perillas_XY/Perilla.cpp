#include "Perilla.h"
#include "hardware/adc.h"
Perilla::Perilla(unsigned int pin, int limite) : patita(pin), maximo(limite) {
    valida = pin >= 26 && pin <= 28 && limite >= 1 && limite <= 65535;
    if (valida) adc_gpio_init(patita); // El ADC ya lo iniciamos en main; aquí preparamos esta patita.
}
int Perilla::convertir(uint16_t valor, int limite) {
    if (limite < 1 || limite > 65535) return 0;
    if (valor > 4095) valor = 4095; // Si llega un valor mayor, lo dejamos en el máximo del ADC.
    // Caso E01: revisar el resultado a mitad de recorrido; esperamos una posición intermedia.
    // Esta variante sirve para comparar el cálculo con la versión 4.
    return (valor / 4095) * limite;
}
void Perilla::leer() {
    cambio = false;
    if (!valida) return;
    // Caso E02: sin elegir el canal, las dos perillas terminaban leyendo el mismo.
    adc_select_input(patita - 26); // Elegimos el canal de esta perilla: GP26 es ADC0, GP27 es ADC1.
    uint32_t suma = 0;
    for (int i = 0; i < 4; ++i) suma += adc_read();
    lectura = suma / 4; // Promediamos cuatro muestras; ayuda a suavizar, pero no elimina todo el ruido.
    const int nueva = convertir(lectura, maximo);
    cambio = nueva != posicion;
    posicion = nueva;
}
