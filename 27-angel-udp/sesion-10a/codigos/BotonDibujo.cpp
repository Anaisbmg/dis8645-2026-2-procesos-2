#include "BotonDibujo.h"
#include "pico/stdlib.h"

// CONSTRUCTOR
//
// Guarda el GPIO y los valores iniciales.
// Todavia no configura el hardware.

BotonDibujo::BotonDibujo(unsigned int pinBoton) {
    pin = pinBoton;

    ultimaLectura = true;
    estadoEstable = true;

    ultimoCambio = 0;

    // 30000 microsegundos = 30 milisegundos.
    tiempoRebote = 30000;
}

// INICIAR
//
// Configuramos el GPIO como entrada.
//
// La resistencia pull-up interna mantiene
// la entrada en 1 cuando el boton esta suelto.
//
// Al presionar, el boton conecta con GND
// y la lectura pasa a 0.

void BotonDibujo::iniciar() {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);

    ultimaLectura = gpio_get(pin);
    estadoEstable = ultimaLectura;

    ultimoCambio = time_us_64();
}

// FUE PRESIONADO
//
// Revisamos si la lectura cambio.
//
// Si cambia, comenzamos a contar el tiempo.
// Si permanece estable durante 30 ms,
// aceptamos el nuevo estado.
//
// Solo devolvemos true cuando el estado
// aceptado pasa de suelto a presionado.

bool BotonDibujo::fuePresionado() {
    bool lecturaActual = gpio_get(pin);
    uint64_t ahora = time_us_64();

    // Cada cambio reinicia el tiempo de espera.
    if (lecturaActual != ultimaLectura) {
        ultimaLectura = lecturaActual;
        ultimoCambio = ahora;
    }

    // Esperamos a que la lectura sea estable.
    if (ahora - ultimoCambio >= tiempoRebote) {
        if (lecturaActual != estadoEstable) {
            estadoEstable = lecturaActual;

            // false equivale a 0:
            // el boton esta presionado.
            if (estadoEstable == false) {
                return true;
            }
        }
    }

    // No hay una nueva pulsacion.
    return false;
}