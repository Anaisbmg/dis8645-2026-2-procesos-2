// Selector.cpp
// implementaciones de la clase

#include "Selector.h"
#include <string.h>

// constructor
Selector::Selector() {
  // letras, espacio, algunos especiales, y al final TAB y ENTER
  Selector::lista = "abcdefghijklmnopqrstuvwxyz .,!?-_@#\t\n";
  Selector::total = strlen(Selector::lista);
}

// avanzar o retroceder, dando la vuelta al llegar al borde
void Selector::mover(int paso) {
  Selector::indice = ((Selector::indice + paso) % Selector::total
                      + Selector::total) % Selector::total;
}

char Selector::actual() {
  return Selector::lista[Selector::indice];
}

// indice del vecino (-1 = anterior, +1 = siguiente)
int Selector::relativo(int desplazamiento) {
  return ((Selector::indice + desplazamiento) % Selector::total
          + Selector::total) % Selector::total;
}

// texto corto para mostrar en pantalla
void Selector::etiqueta(int i, char* destino) {
  char c = Selector::lista[i];

  if (c == '\t') {
    strcpy(destino, "TAB");
  }
  else if (c == '\n') {
    strcpy(destino, "ENT");
  }
  else if (c == ' ') {
    strcpy(destino, "SPC");
  }
  else {
    destino[0] = c;
    destino[1] = '\0';
  }
}

// a-z pasa a A-Z, el resto queda igual
char Selector::mayuscula(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 32;
  }
  return c;
}