#ifndef BOTON_H
#define BOTON_H

// uno de los botones servirá como botón
// encendido o apagado / mantener apretado
// y seleccionador / un toque

// el otro botón servirá para mantener al personaje volando

// promesas de lo que queremos que el botón haga
class Boton
{

    // atributos

    // tiempo presionado

    // constructor
    Boton(int nuevaPatita);

    // botón1: dos variables
    // if boton presionado >= 2sg
    // la pantalla se inicia
    // si se vuelve a apretar por 2sg
    // la pantalla se apaga

    // la segunda opción de este botón
    // if boton presionado <= 2sg
    // recorrer personajes con perilla2
    // presionar botón <= 2sg

    // botón2: una variable
    // si presionado = true
    // el personaje baja
    // si presionado = false
    // el personaje sube
};

#endif