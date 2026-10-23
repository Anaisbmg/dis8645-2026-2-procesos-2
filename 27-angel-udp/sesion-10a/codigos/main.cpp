#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#include "Perilla.h"
#include "Pantalla.h"
#include "BotonDibujo.h"

// PROYECTO: ETCH A SKETCH DIGITAL
//
// Lapiz abajo:
// dejamos un trazo blanco.
//
// Lapiz levantado:
// mostramos una cruz amarilla,
// pero no modificamos el dibujo.

// OBJETOS

Perilla perillaX(26);
Perilla perillaY(27);

Pantalla pantalla(17, 16);

BotonDibujo botonBorrar(10);
BotonDibujo botonLapiz(11);

// COLORES DEL DIBUJO

const uint16_t NEGRO = 0x0000;
const uint16_t BLANCO = 0xFFFF;

int main() {
    stdio_init_all();

    adc_init();

    perillaX.iniciar();
    perillaY.iniciar();

    pantalla.iniciar();
    pantalla.limpiar(NEGRO);

    botonBorrar.iniciar();
    botonLapiz.iniciar();

    bool lapizAbajo = true;

    perillaX.leer();
    perillaY.leer();

    int xAnterior = perillaX.convertir(
        0, pantalla.ancho - 1
    );

    int yAnterior = perillaY.convertir(
        0, pantalla.alto - 1
    );

    pantalla.punto(xAnterior, yAnterior, BLANCO);

    printf("Sistema iniciado. Lapiz abajo.\n");

    while (true) {
        // LEER LAS PERILLAS

        perillaX.leer();
        perillaY.leer();

        int x = perillaX.convertir(
            0, pantalla.ancho - 1
        );

        int y = perillaY.convertir(
            0, pantalla.alto - 1
        );

        // REVISAR LOS BOTONES

        bool borrar = botonBorrar.fuePresionado();
        bool cambiarLapiz = botonLapiz.fuePresionado();

        bool seMovio =
            (x != xAnterior || y != yAnterior);

        // Solo actualizamos la pantalla
        // si ocurrio alguna accion.
        if (seMovio || borrar || cambiarLapiz) {

            // RETIRAR EL CURSOR ANTERIOR
            //
            // Si el lapiz estaba levantado,
            // habia una cruz en su posicion anterior.
            //
            // Recuperamos el dibujo que tenia debajo.

            if (!lapizAbajo) {
                pantalla.cursor(
                    xAnterior, yAnterior, false
                );
            }

            // CAMBIAR EL ESTADO DEL LAPIZ

            if (cambiarLapiz) {
                lapizAbajo = !lapizAbajo;

                // Evitamos conectar con una
                // posicion anterior al cambio.
                xAnterior = x;
                yAnterior = y;

                if (lapizAbajo) {
                    pantalla.punto(x, y, BLANCO);
                    printf("Lapiz abajo: dibujando.\n");
                } else {
                    printf("Lapiz levantado: cursor amarillo.\n");
                }
            }

            // BORRAR

            if (borrar) {
                pantalla.limpiar(NEGRO);

                xAnterior = x;
                yAnterior = y;

                if (lapizAbajo) {
                    pantalla.punto(x, y, BLANCO);
                }

                printf("Dibujo borrado.\n");
            }

            // DIBUJAR

            if (lapizAbajo &&
                (x != xAnterior || y != yAnterior)) {

                pantalla.linea(
                    xAnterior, yAnterior,
                    x, y,
                    BLANCO
                );
            }

            // Siempre guardamos la posicion actual,
            // incluso sin dibujar.
            xAnterior = x;
            yAnterior = y;

            // MOSTRAR EL CURSOR NUEVO
            //
            // Solo aparece con el lapiz levantado.

            if (!lapizAbajo) {
                pantalla.cursor(x, y, true);
            }

            if (seMovio) {
                printf("X: %d | Y: %d\n", x, y);
            }
        }

        sleep_ms(20);
    }
}