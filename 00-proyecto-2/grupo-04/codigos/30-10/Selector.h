#ifndef SELECTOR_H
#define SELECTOR_H


// Selector.h
// declaraciones de la clase Selector
// guarda la lista de caracteres y cual esta elegido


class Selector {

  // todo publico
  public:

  // atributos
  const char* lista;            // todos los caracteres disponibles
  int total;
  int indice = 0;               // el que esta elegido ahora


  // constructor
  Selector();

  // metodos
  void mover(int paso);
  char actual();
  int relativo(int desplazamiento);
  void etiqueta(int i, char* destino);
  static char mayuscula(char c);

};

#endif