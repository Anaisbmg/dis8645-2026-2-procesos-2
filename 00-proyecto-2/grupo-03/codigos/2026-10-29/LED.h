
//// MAQUETA CODIGO ////

// LED del modo 03 - Minijuego
// Se enciende cuando la perilla selecciona el modo juego.

#pragma once
#include <stdio.h>

// atributos

const int pinLed = 13; // GPIO13 de la Raspberry Pi Pico.

// metodos

void iniciarLed(); // configura el pin del LED.

void actualizarLed(int modoActual); // enciende o apaga el LED según el modo.
