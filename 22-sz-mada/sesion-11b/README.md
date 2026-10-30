# sesion-11b

2026.10.30

## apuntes sesión

Implementé la clase botón del grupo 1 en nuestro código main.cpp de la simulación de Wokwi

Pegaré &darr; aquí &darr; el código y comentaré en los cambios que hice

```cpp
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "Perilla.h"
#include "BotonGrupo1.h" // Obviamente tuve que añadir BotonGrupo1.h
extern "C" {
#include "ssd1306.h"
}

int main() {
    stdio_init_all(); adc_init();
    Perilla horizontal(26, 127), vertical(27, 63);
    // Se definen los pines de los botones en el codigo
    BotonGrupo1 botonModo(14);
    BotonGrupo1 botonBorrar(15);

    i2c_init(i2c0, 400000);
    gpio_set_function(4, GPIO_FUNC_I2C); gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4); gpio_pull_up(5);
    ssd1306_t pantalla{}; pantalla.external_vcc = false;
    if (!ssd1306_init(&pantalla, 128, 64, 0x3c, i2c0)) {
        printf("No se pudo reservar la pantalla.\n");
        while (true) tight_loop_contents();
    }

    uint64_t lecturaAnterior = 0, informeAnterior = 0;
    // Agrego un boolean para poder reconocer cuando TRAZO esta en modo DIBUJO
    // Y cuando esta en modo MOVER
    // Comienza en MOVER para no dibujar nada por accidente
    bool dibujando = false;
    bool primera = true;

    while (true) {
        const uint64_t ahora = time_us_64();
        
        botonModo.leer(); // Para alternar entre modo DIBUJAR y MOVER
        botonBorrar.leer(); // Para poder asignar Borrar a uno de los botones
        botonModo.presionarSwitch(); // presionarSwitch es un boolean que nos permite diferenciar entre dos estados (DIBUJAR / MOVER)
        dibujando = botonModo.estadoPresionarSwitch; // si estadoPresionarSwitch es true, entonces se habilita DIBUJAR
        if (botonBorrar.recienPresionado) { // if statement para el boton Borrar
          ssd1306_clear(&pantalla); // Borra todo en la pantalla
          ssd1306_show(&pantalla); // Instantaneamente rehabilita la pantalla
        }

        if (ahora - lecturaAnterior >= 20000) {
            lecturaAnterior = ahora;
            horizontal.leer(); vertical.leer();
            if (primera || horizontal.cambio || vertical.cambio) {
                ssd1306_clear(&pantalla);
                ssd1306_draw_pixel(&pantalla, horizontal.posicion, vertical.posicion);
                ssd1306_show(&pantalla);
                primera = false;
            }
        }

        if (ahora - informeAnterior >= 200000) {
            informeAnterior = ahora;
            // Agregué un condicional que muestre en que estado se encuentra TRAZO
            printf("X=%d Y=%d ADC_X=%u ADC_Y=%u\n", dibujando ? "DIBUJAR" : "MOVER",
            horizontal.posicion,
            vertical.posicion,
            unsigned(horizontal.lectura),
            unsigned(vertical.lectura));
        }
        tight_loop_contents();
    }
}
```

Tristemente, de momento la simulación de Wokwi no funciona ya que lanza un error relacionado a la pantalla (SSD1306), así que mientras no solucionemos eso, no sabremos si TRAZO funciona como se espera

---
