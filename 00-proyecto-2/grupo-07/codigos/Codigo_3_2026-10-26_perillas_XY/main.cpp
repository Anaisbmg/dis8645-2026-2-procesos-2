#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "Perilla.h"
extern "C" { // La biblioteca de pantalla está en C; así la podemos llamar desde nuestro C++.
#include "Ssd1306.h"
}
// Código 3: nuestras dos perillas mueven el cursor. El trazo y los botones vienen después.
int main() {
    // 1. PREPARAR ENTRADAS Y RANGOS
    // Ahora reemplazamos la preparación suelta de pines por dos objetos Perilla.
    stdio_init_all(); adc_init();
    Perilla horizontal(26, 127), vertical(27, 63);
    // 2. PREPARAR PANTALLA Y TIEMPOS
    // La pantalla que estaba pendiente ya tiene bus, dirección y memoria.
    i2c_init(i2c0, 400000);
    gpio_set_function(4, GPIO_FUNC_I2C); gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4); gpio_pull_up(5);
    ssd1306_t pantalla{}; pantalla.external_vcc = false;
    // Aquí revisamos que se haya podido reservar la memoria para la pantalla.
    // Ojo: esto solo no confirma que la pantalla física haya respondido por I2C.
    if (!ssd1306_init(&pantalla, 128, 64, 0x3c, i2c0)) {
        printf("No se pudo reservar la pantalla.\n");
        while (true) tight_loop_contents();
    }
    uint64_t lecturaAnterior = 0, informeAnterior = 0;
    bool primera = true;
    // 3. LEER, ACTUALIZAR Y MOSTRAR
    // El diagnóstico de la versión 2 ahora acompaña la lectura y el cursor real.
    // 4. INTEGRAR DIBUJO Y BOTONES: todavía pendiente; aquí sólo movemos un punto.
    while (true) {
        const uint64_t ahora = time_us_64();
        if (ahora - lecturaAnterior >= 20000) {
            lecturaAnterior = ahora;
            horizontal.leer(); vertical.leer(); // Cada perilla elige su canal antes de leer, para que X e Y sean independientes.
            if (primera || horizontal.cambio || vertical.cambio) {
                ssd1306_clear(&pantalla); // Limpiamos el cursor anterior; en esta versión todavía no guardamos el dibujo.
                ssd1306_draw_pixel(&pantalla, horizontal.posicion, vertical.posicion);
                ssd1306_show(&pantalla); // Mandar la imagen por I2C toma tiempo, aunque no agreguemos sleep.
                primera = false;
            }
        }
        // 5. REVISAR RESULTADOS
        // Mostramos las lecturas y las coordenadas para revisar cada eje.
        if (ahora - informeAnterior >= 200000) {
            informeAnterior = ahora;
            printf("X=%d Y=%d ADC_X=%u ADC_Y=%u\n", horizontal.posicion,
                   vertical.posicion, unsigned(horizontal.lectura), unsigned(vertical.lectura));
        }
        tight_loop_contents();
    }
}
