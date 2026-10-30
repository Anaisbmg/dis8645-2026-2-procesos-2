// Editor.cpp
// implementaciones de la clase

#include "Editor.h"

// constructor
Editor::Editor() {
  Editor::texto[0] = '\0';
}

// agrega un caracter en la posicion del cursor
void Editor::insertar(char c) {
  if (Editor::largo >= MAX_TEXTO) {
    return;
  }

  // correr todo lo que esta a la derecha para hacer espacio
  for (int i = Editor::largo; i > Editor::cursor; i--) {
    Editor::texto[i] = Editor::texto[i - 1];
  }

  Editor::texto[Editor::cursor] = c;
  Editor::cursor++;
  Editor::largo++;
  Editor::texto[Editor::largo] = '\0';
}

// borra el caracter que esta antes del cursor (como backspace)
void Editor::borrar() {
  if (Editor::cursor <= 0) {
    return;
  }

  for (int i = Editor::cursor - 1; i < Editor::largo - 1; i++) {
    Editor::texto[i] = Editor::texto[i + 1];
  }

  Editor::cursor--;
  Editor::largo--;
  Editor::texto[Editor::largo] = '\0';
}

void Editor::borrarTodo() {
  Editor::largo = 0;
  Editor::cursor = 0;
  Editor::texto[0] = '\0';
}

// mover el cursor sin salirse del texto
void Editor::moverCursor(int paso) {
  Editor::cursor += paso;

  if (Editor::cursor < 0) {
    Editor::cursor = 0;
  }
  if (Editor::cursor > Editor::largo) {
    Editor::cursor = Editor::largo;
  }
}

// como se ve cada caracter en el LCD
char Editor::simbolo(int i) {
  char c = Editor::texto[i];

  if (c == '\t') {
    return 0x7E;   // flecha derecha
  }
  if (c == '\n') {
    return 0x7F;   // flecha izquierda (retorno)
  }
  return c;
}