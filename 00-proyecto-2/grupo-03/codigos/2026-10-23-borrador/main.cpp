// incluir bibliotecas estandar
#include <stdio.h>
#include "pico/stdlib.h"

// incluir mis bibliotecas
#include "MaquinaEmociones.h"

MaquinaEmociones maquinita;

int main()
{
    stdio_init_all();

    // inicial
    // configurar las perillas
    // perillaEmociones.definirOpciones(5);
    //  perillaNavegacion.definirOpciones(7);

    // dentro de while(true)
    // va todo lo que se repite
    while (true)
    {

        // hacer las lecturas de sensores
        maquinita.actualizar();

   

     // tomar decisiones al respecto
        // de las lecturas de sensores

        if (maquinita.sad) {
           maquinita.mostrarPantalla(emo);
        }

        // hacer que actuadores
        // responden a lo calculado

        // por ejemplo
        // pantallita.emitirMensaje(OK);
        // luz.parpeadear(brigido);

        // esta pausa viene en wokwi
        // pero no es necesaria
        sleep_ms(250);
    }
}