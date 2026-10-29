//// MAQUETA CODIGO ////

// modo 01 de pantalla (modoActual = 0)
// muestra mensajes motivacionales o afirmaciones
// nota: por ahora este archivo se incluye solo desde main.cpp.
// Al convertirlo en clase se evita que los nombres choquen con los de otros archivos.

#pragma once
#include <stdio.h>   // necesario para printf

// atributos
const char* mensajes[] = {
    "Eres capaz de lograr grandes cosas.",
    "Cada dia es una nueva oportunidad.",
    "Confia en ti mismo y en tus habilidades.",
    "El exito es la suma de pequenos esfuerzos.",
    "Nunca es tarde para perseguir tus suenos."   // sin "ñ": la fuente de la pantalla podria no tenerla
};
// mensajes de ejemplos hasta el momento
// hay que mejorarlos siosi

int cantidadMensajes = sizeof(mensajes) / sizeof(mensajes[0]); // se calcula sola: cantidad de mensajes motivacionales
int mensajeActual = 0;    // mensaje que se esta mostrando actualmente
int mensajeDibujado = -1; // ultimo mensaje dibujado (-1 = ninguno). Evita redibujar sin necesidad


// metodos
void entrarMensajes() // Se llama al entrar al modo: vuelve al primer mensaje y fuerza a dibujarlo.
{
    mensajeActual = 0;
    mensajeDibujado = -1;
}

void siguienteMensaje() // Avanza al próximo mensaje y vuelve al primero cuando llega al final.
{
    mensajeActual++;
    if (mensajeActual >= cantidadMensajes) {
        mensajeActual = 0;
    }
}

void dibujarMensaje() // Dibuja el mensaje actual, solo si cambió.
{
    if (mensajeActual == mensajeDibujado) return;
    mensajeDibujado = mensajeActual;

    // Aquí iría el código para dibujar el texto en la pantalla.
    // Por ahora, solo imprimimos el texto en la consola.
    printf("%s\n", mensajes[mensajeActual]);
}