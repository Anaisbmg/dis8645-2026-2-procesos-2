#include "Encoder.h"
#include "hardware/gpio.h"
Encoder::Encoder(unsigned int clk, unsigned int dt, int cantidad, bool invertir)
    : clk_(clk), dt_(dt), cantidad_(cantidad), invertir_(invertir) {
    valida = clk <= 28 && dt <= 28 && clk != dt && cantidad > 0;
    if (!valida) return;
    gpio_init(clk_); gpio_set_dir(clk_, GPIO_IN); gpio_pull_up(clk_);
    gpio_init(dt_); gpio_set_dir(dt_, GPIO_IN); gpio_pull_up(dt_);
    anterior_ = (gpio_get(clk_) << 1) | gpio_get(dt_);
}
void Encoder::leer() {
    direccion = 0;
    if (valida) procesar(gpio_get(clk_), gpio_get(dt_));
}
void Encoder::procesar(bool clk, bool dt) {
    direccion = 0;
    if (!valida) return;
    const int actual = (int(clk) << 1) | int(dt);
    // Si cambian las dos señales a la vez, puede faltar una lectura; descartamos ese paso.
    if ((actual ^ anterior_) == 3) {
        acumulado_ = 0; anterior_ = actual; return;
    }
    static const int paso[16] = {0,-1,1,0, 1,0,0,-1, -1,0,0,1, 0,1,-1,0};
    acumulado_ += paso[(anterior_ << 2) | actual];
    anterior_ = actual;
    // Contamos un evento cuando completamos la secuencia y volvemos al reposo 11.
    // Falta revisar cuántas transiciones tiene cada clic del encoder físico.
    if (actual == 3) {
        if (acumulado_ == 4) direccion = 1;
        else if (acumulado_ == -4) direccion = -1;
        acumulado_ = 0;
        if (invertir_) direccion = -direccion;
        // Caso E03: -1 % 5 daba -1. Sumamos cantidad antes para volver a la última opción.
        posicion = (posicion + direccion + cantidad_) % cantidad_;
    }
}
