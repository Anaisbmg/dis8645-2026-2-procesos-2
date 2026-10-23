#ifndef PANTALLA_H
#define PANTALLA_H

#include <stdint.h>

// Vamos a tener una pantalla.
//
// La pantalla recibira instrucciones
// desde la Raspberry Pi Pico.
//
// Por ahora necesitamos:
//
// iniciar la pantalla,
// pintar el fondo,
// dibujar un punto.
//
// Todos los atributos y metodos
// estaran en public.

class Pantalla {
public:
    // ATRIBUTOS

    unsigned int pinCS;
    unsigned int pinDC;

    int ancho;
    int alto;

    // CONSTRUCTOR
    // Recibe los GPIO de seleccion y control.
    Pantalla(unsigned int cs, unsigned int dc);

    // METODOS DE COMUNICACION

    // Envia una instruccion a la pantalla.
    void comando(uint8_t valor);

    // Envia un dato a la pantalla.
    void dato(uint8_t valor);

    // Selecciona el rectangulo que recibira pixeles.
    void ventana(int x0, int y0, int x1, int y1);

    // METODOS DE DIBUJO

    void iniciar();

    void limpiar(uint16_t color);

    void punto(int x, int y, uint16_t color);
    
    // Dibuja una linea entre dos posiciones.
    //
    // x0, y0: posicion inicial.
    // x1, y1: posicion final.
    void linea(int x0, int y0, int x1, int y1, uint16_t color);

   // MEMORIA DEL DIBUJO
    //
    // Nuestro dibujo solo utiliza blanco y negro.
    // Guardamos un bit por pixel:
    //
    // 0: fondo negro.
    // 1: trazo blanco.
    //
    // 320 * 240 / 8 = 9600 bytes.
    uint8_t dibujo[9600] = {};

    // Pinta un pixel en la pantalla
    // sin modificar la memoria del dibujo.
    void pixelDirecto(int x, int y, uint16_t color);

    // Muestra el cursor o restaura lo que habia debajo.
    void cursor(int x, int y, bool mostrar);
};

#endif