// En este archivo determinaremos que es el botón(atributos) y que hace(funciones)
// Los dos botones son de la misma clase, lo que cambia es qué gestos usa cada uno en el main
// Aquí creamos la clase con todos los atributos y funciones que tienen los dos botones
#ifndef BOTON2_H
#define BOTON2_H
// Evita que el compilador lea el archivo dos veces, al final del código se cierra con un #endif
#include "hardware/gpio.h"
#include "pico/stdlib.h"
// Esto incluye dos bibliotecas para Raspberry Pi que nos da funciones para:
// hardware/gpio.h
//  permite leer fácilmente señales de entrada y de salida a través de los pines y así no tener
//  que escribir comandos o funciones más complejas.(hardware/gpio.h)
// pico/stdlib.h
//  Una biblioteca básica para el modelo pico
//  que nos proporciona funciones de tiempo y uint32_t

// A continuación creamos un tipo que se llama EstadoBoton que solo puede tener los 3 valores dentro de las llaves.
// IMPORTANTE: En Boton2.cpp determinaremos como lo hace o como va a llegar a esos valores.
enum class EstadoBoton
// Aquí anunciamos las posiblidades de estados que puede tener el botón, que en este caso son 3
{
    REPOSO, // sin presionar
    PRESIONADO,
    ESPERANDO_PRESION // estado entre presionados para ver si llega otra presión
};

// Creamos un tipo que se llama Gesto que puede tener los valores que determinamos dentro de las llaves.
enum class Gesto
// Aquí anunciamos los posibles gestos o acciones que podemos hacer con cualquiera de los dos botones
{
    NADA,
    PULSADO1VEZ,      // Un solo clic corto
    PULSADO2VECES,    // Pasa a la siguiente fotografia
    PULSADO3VECES,    // Activa modo carrusel de fotografias
    PULSACIONLARGA,   // Entre 1 y 5 segundos, abre la carpeta (no vuelve al escritorio)
    PULSACIONMUYLARGA // Más de 5 segundos, vuelve al escritorio
};

// Definimos la clase boton
class Boton2
{

    // Lo hacemos público para que los miembros declarados del proyecto puedan interactuar unos con otros sin restricciones
public:
    // A continuación definimos los atributos del botón
    // pin donde está conectado el botón
    int pin;
    // en qué paso va el botón
    EstadoBoton estado = EstadoBoton::REPOSO;
    // gesto detectado que todavía no ha leído el main
    Gesto gestoPendiente = Gesto::NADA;
    // true mientras el botón está apretado
    bool presionado = false;
    // cuántas presiones seguidas van
    int numeroPresiones = 0;

    // tiempos en milisegundos
    // momento del último cambio de estado
    uint32_t instanteCambio = 0;
    // duración de la pulsación larga
    uint32_t tiempoLargo = 1000;
    // duración de la pulsación muy larga
    uint32_t tiempoMuyLargo = 5000;
    // tiempo máximo de espera entre una presión y la siguiente
    uint32_t tiempoEntrePresionado = 400;

    // A continuación definimos el constructor y los métodos
    // constructor: recibe el pin donde está conectado el botón
    Boton2(int pin);
    // revisa el botón, se llama en cada vuelta del while
    void leer();
    // entrega el gesto detectado y lo borra para no repetirlo
    Gesto leerGesto();
};

#endif
