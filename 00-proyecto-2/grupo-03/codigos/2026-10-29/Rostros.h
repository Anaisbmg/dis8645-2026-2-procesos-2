//// MAQUETA CODIGO ////
// ilustraciones (bitmaps) de cada emocion
 
#pragma once
#include <stdint.h>
 
// PLACEHOLDER: estos arreglos estan en blanco (todo ceros).
// Reemplazarlos por los bitmaps reales cuando se defina la pantalla.
// Formato de ejemplo: 1 bit por pixel, 64 x 64 pixeles = 512 bytes por rostro.
// El tamano y el formato reales dependen de la pantalla que se use.
const int ANCHO_ROSTRO = 64;
const int ALTO_ROSTRO = 64;
 
// const -> los arreglos quedan en la memoria flash, no en la RAM
const uint8_t rostroFelicidad[512] = {0};
const uint8_t rostroTristeza[512]  = {0};
const uint8_t rostroEnojo[512]     = {0};
const uint8_t rostroCalma[512]     = {0};