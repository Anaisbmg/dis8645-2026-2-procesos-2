//// MAQUETA CODIGO ////

// modo 02 de pantalla (modoActual = 1)
// muestra ilustraciones de expresiones faciales
// nota: por ahora este archivo se incluye solo desde main.cpp.
// Al convertirlo en clase se evita que los nombres choquen con los de otros archivos.
 
#pragma once
#include <stdio.h>
#include <stdint.h>
#include "Rostros.h"   // bitmaps de cada emocion
 
// atributos
 
// 0 = Felicidad, 1 = Tristeza, 2 = Enojo, 3 = Calma
const char* emociones[4] = {
    "Felicidad",
    "Tristeza",
    "Enojo",
    "Calma"
};
 
// nivel de dificultad del juego
int dificultades[4] = {
    3, // Felicidad: velocidad media, obstaculos moderados
    2, // Tristeza: velocidad lenta, pocos obstaculos
    4, // Enojo: velocidad muy rapida, obstaculos muy frecuentes
    1  // Calma: velocidad muy lenta, muy pocos obstaculos
};
 
// ilustracion de cada emocion, en el mismo orden que emociones[]
const uint8_t* rostros[4] = {
    rostroFelicidad,
    rostroTristeza,
    rostroEnojo,
    rostroCalma
};
 
int indiceActual = 0;      // la emoción que se está viendo en pantalla.
int ultimoDibujado = -1;   // la última emoción dibujada (-1 = ninguna). evita redibujar sin necesidad.
 
// metodos
 
void entrarEmociones() // se llama al entrar al modo: fuerza a dibujar de nuevo el rostro.
{
    ultimoDibujado = -1;
}
 
void actualizarEmocion(int opcion) // guarda la opción que viene de la perilla como emoción actual.
{
    if (opcion < 0) opcion = 0;
    if (opcion > 3) opcion = 3;
    indiceActual = opcion;
}
 
int emocionSeleccionada() // devuelve el índice de la emoción elegida.
{
    return indiceActual;
}
 
const char* obtenerNombre(int emocion) // devuelve el nombre de esa emoción.
{
    return emociones[emocion];
}
 
int obtenerDificultad(int emocion) // devuelve el nivel de dificultad (1 a 4) de esa emoción.
{
    return dificultades[emocion];
}
 
void dibujarEmocion() // dibuja el rostro de la emoción actual, solo si cambió.
{
    if (indiceActual == ultimoDibujado) return;
    ultimoDibujado = indiceActual;
 
    // por ahora solo imprimimos el nombre en la consola.
    printf("Emocion: %s\n", emociones[indiceActual]);
 
    // TODO: cuando exista la libreria de la pantalla, dibujar el bitmap:
    // dibujarBitmap(rostros[indiceActual], ANCHO_ROSTRO, ALTO_ROSTRO);
}

