#ifndef BOTON_DIBUJO_H
#define BOTON_DIBUJO_H

#include <stdint.h>

// Vamos a tener dos botones.
//
// Ambos detectan pulsaciones,
// pero cada uno tendra una funcion diferente.
//
// La clase solo detecta la pulsacion.
// main.cpp decide que hacer con ella.

class BotonDibujo {
public:
    // ATRIBUTOS

    unsigned int pin;

    // Ultima lectura directa del GPIO.
    bool ultimaLectura;

    // Estado que aceptamos como estable.
    bool estadoEstable;

    // Momento en que cambio la lectura.
    uint64_t ultimoCambio;

    // Tiempo necesario para aceptar un cambio.
    // Se expresa en microsegundos.
    uint64_t tiempoRebote;

    // CONSTRUCTOR
    BotonDibujo(unsigned int pinBoton);

    // METODOS

    // Prepara el GPIO con resistencia interna.
    void iniciar();

    // Devuelve true una sola vez
    // por cada pulsacion aceptada.
    //
    // Debemos llamarlo continuamente.
    bool fuePresionado();
};

#endif