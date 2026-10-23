// incluir bibliotecas estandar
#include <stdio.h>
#include "pico/stdlib.h"

// incluir mis bibliotecas
// include Perilla
// include Boton

// crear las instancias de perilla

// perilla conectada a GP8, por ejemplo
Perilla perillaEmociones(8);

// perilla conectada a GP10, por ejemplo
Perilla perillaNavegacion(10);

int main()
{
    stdio_init_all();

    // inicial
    // configurar las perillas
    perillaEmociones.definirOpciones(5);
    perillaNavegacion.definirOpciones(7);

    // dentro de while(true)
    // va todo lo que se repite
    while (true)
    {
        // hacer las lecturas de sensores
        perillaEmociones.leerValor();
        perillaNavegacion.leerValor();

        // tomar decisiones al respecto
        // de las lecturas de sensores

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