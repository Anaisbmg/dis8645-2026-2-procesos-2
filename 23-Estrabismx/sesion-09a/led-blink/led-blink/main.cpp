// codigo de prueba generado por gemini

#include "pico/stdlib.h"

// Definimos el pin GPIO donde conectaste el LED
const uint LED_PIN = 15;

int main() {
    // Inicializa la E/S estándar (útil si luego agregas prints por UART/USB)
    stdio_init_all();

    // Inicializa el pin GP15
    gpio_init(LED_PIN);
    
    // Configura el GP15 como salida
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        // Enciende el LED
        gpio_put(LED_PIN, 1);
        sleep_ms(500); // Espera 500 ms

        // Apaga el LED
        gpio_put(LED_PIN, 0);
        sleep_ms(500); // Espera 500 ms
    }

    return 0;
}