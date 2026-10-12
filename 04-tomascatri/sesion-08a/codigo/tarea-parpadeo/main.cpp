// hay 3 elementos
// lucecita
// perilla
// pulsador

// lucecita necesita R de 220
// perilla necesita nada
// pulsador necesita R de 10k

// entradas
// o sensores
// perilla - posicion rotacional / giro
// pulsador - si o no hay presion

// salidas
// o actuadores
// lucecita

// ya pero y?

// pulsador: prender y apagar todo
// potenciometro: frecuencia de parpadeo

// lucecita: prender y apagarse
// segun lo que diga boton y perilla

// por lo tanto
// boton tiene dos estados
// prendido y apagado

// perilla va a tener
// una posicion que va a ser
// usada por el sistema
// para impactar en parpadeo lucecita



#include <stdio.h>
#include "pico/stdlib.h"
#include "Boton.h"
#include "Perilla.h"
#include "Lucecita.h"

// Función para mapear un rango de valores a otro
long mapear(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main() {
    stdio_init_all();

    Boton pulsador(7);     // Botón en GP7
    Perilla parpadeo(26);  // Potenciómetro en GP26 (ADC0)
    Lucecita luz(6);       // LED en GP6

    bool sistemaActivo = true;
    bool ultimoEstadoBoton = false;

    uint32_t tiempoAnterior = 0;
    bool estadoLed = false;

    while (true) {
        // 1. Lectura de periféricos
        pulsador.leer();
        parpadeo.leer();

        // 2. Control de encendido/apagado general con el botón (detección de flanco)
        if (pulsador.presionado && !ultimoEstadoBoton) {
            sistemaActivo = !sistemaActivo;
            if (!sistemaActivo) {
                luz.apagar();
                estadoLed = false;
            }
        }
        ultimoEstadoBoton = pulsador.presionado;

        // 3. Parpadeo paramétrico si el sistema está activo
        if (sistemaActivo) {
            // Se parametriza el intervalo entre 50 ms (rápido) y 1000 ms (lento)
            uint32_t intervalo = mapear(parpadeo.posicion, 0, 4095, 50, 1000);

            uint32_t tiempoActual = to_ms_since_boot(get_absolute_time());

            if (tiempoActual - tiempoAnterior >= intervalo) {
                tiempoAnterior = tiempoActual;
                estadoLed = !estadoLed;

                if (estadoLed) {
                    luz.prender();
                } else {
                    luz.apagar();
                }
            }
        }

        sleep_ms(10); // Pausa pequeña para estabilizar el bucle y evitar rebotes
    }

    return 0;
}