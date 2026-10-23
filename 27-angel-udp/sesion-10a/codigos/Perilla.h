#ifndef PERILLA_H
#define PERILLA_H

#include <stdint.h>

// Vamos a tener dos perillas.
//
// Ambas funcionan de la misma manera,
// pero cada una tendra su propio pin.
//
// Esta clase solo lee la perilla
// y convierte su lectura a otro rango.
//
// Mas adelante usaremos esos valores
// para controlar el lapiz de la pantalla.

class Perilla {
public:
    // ATRIBUTOS
    // Son datos que guarda cada objeto.

    // GPIO donde conectamos la senal.
    unsigned int pin;

    // Ultima lectura obtenida del ADC.
    uint16_t lectura;

    // CONSTRUCTOR
    // Recibe el GPIO que usara esta perilla.
    Perilla(unsigned int pinADC);

    // METODOS
    // Son acciones que puede realizar el objeto.

    // Prepara el GPIO para una lectura analogica.
    void iniciar();

    // Lee la perilla y guarda el resultado.
    // Devuelve un numero entre 0 y 4095.
    uint16_t leer();

    // Convierte la ultima lectura guardada
    // al rango que necesitemos.
    int convertir(int minimo, int maximo);
};

#endif