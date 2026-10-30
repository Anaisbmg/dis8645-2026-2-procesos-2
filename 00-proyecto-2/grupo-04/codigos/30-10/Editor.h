#ifndef EDITOR_H
#define EDITOR_H


// Editor.h
// declaraciones de la clase Editor
// guarda el texto digitado y la posicion del cursor


// 20 columnas x 4 filas
#define MAX_TEXTO 80


class Editor {

  // todo publico
  public:

  // atributos
  char texto[MAX_TEXTO + 1];
  int largo = 0;
  int cursor = 0;               // el cursor esta ANTES del caracter texto[cursor]


  // constructor
  Editor();

  // metodos
  void insertar(char c);
  void borrar();
  void borrarTodo();
  void moverCursor(int paso);
  char simbolo(int i);

};

#endif