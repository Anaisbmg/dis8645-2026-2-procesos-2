
#include <Arduino.h>
#include "Led.h"

// metodos

void iniciarLed() // configura el LED como salida.
{
    pinMode(pinLed, OUTPUT);
    digitalWrite(pinLed, LOW);
}

void actualizarLed(int modoActual) // controla el LED según el modo actual.
{
    if (modoActual == 2)
    {
        digitalWrite(pinLed, HIGH); // enciende el LED en el modo juego.
    }
    else
    {
        digitalWrite(pinLed, LOW); // apaga el LED en los otros modos.
    }
}
