#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"
// Código 2: dejamos lista la estructura. Todavía no leemos las perillas ni dibujamos.
int main() {
    // 1. PREPARAR ENTRADAS Y RANGOS
    // Del plan anterior ya pasamos a iniciar la comunicación y el ADC.
    stdio_init_all();
    adc_init(); // Iniciamos el ADC una vez; después lo van a compartir nuestras perillas.
    adc_gpio_init(26); adc_gpio_init(27);
    // 2. PREPARAR PANTALLA Y TIEMPOS
    // Ya medimos el tiempo; la pantalla y sus coordenadas siguen pendientes.
    uint64_t anterior = time_us_64();
    // 3. LEER, ACTUALIZAR Y MOSTRAR
    // Aquí sólo comprobamos que el ciclo siga activo. Falta leer las dos perillas.
    // 4. INTEGRAR DIBUJO Y BOTONES: lo dejamos para después de probar las entradas.
    // 5. REVISAR RESULTADOS: por ahora observamos el mensaje del monitor.
    while (true) {
        const uint64_t ahora = time_us_64();
        if (ahora - anterior >= 1000000) {
            anterior = ahora;
            printf("TRAZO: estructura lista; ADC GP26/27 configurado.\n");
        }
        tight_loop_contents(); // Dejamos que el ciclo siga, sin agregar una espera fija.
    }
}
