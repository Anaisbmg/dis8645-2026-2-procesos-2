// esto venia en wokwi
#include <stdio.h>
#include "pico/stdlib.h"

// incluir mis archivos
#include "Boton.h"
#include "Perilla.h"
#include "Pantalla.h"
#include "Selector.h"
#include "Editor.h"


// dibuja el texto digitado en la pantalla 1 (20x4)
void dibujarTexto(Pantalla &pantalla, Editor &editor) {

  char linea[21];

  for (int fila = 0; fila < 4; fila++) {
    for (int col = 0; col < 20; col++) {
      int i = fila * 20 + col;
      linea[col] = (i < editor.largo) ? editor.simbolo(i) : ' ';
    }
    linea[20] = '\0';
    pantalla.escribirLinea(fila, linea);
  }

  // dejar el cursor parpadeando donde corresponde
  int pos = editor.cursor;
  if (pos > 79) {
    pos = 79;
  }
  pantalla.moverCursor(pos / 20, pos % 20);
}

// dibuja el carrusel de caracteres en la pantalla 2
void dibujarSelector(Pantalla &pantalla, Selector &selector) {

  char linea[40];
  char anterior[8];
  char actual[8];
  char siguiente[8];

  selector.etiqueta(selector.relativo(-1), anterior);
  selector.etiqueta(selector.indice, actual);
  selector.etiqueta(selector.relativo(1), siguiente);

  snprintf(linea, sizeof(linea), "SELECTOR      %2d/%2d",
           selector.indice + 1, selector.total);
  pantalla.escribirLinea(0, linea);

  snprintf(linea, sizeof(linea), "%-5s [%-3s] %-5s", anterior, actual, siguiente);
  pantalla.escribirLinea(1, linea);
}


int main() {

  stdio_init_all();

  // pantalla 1 (texto) en I2C0 y pantalla 2 (selector) en I2C1
  Pantalla pantallaTexto(i2c0, 4, 5);
  Pantalla pantallaSelector(i2c1, 6, 7);

  // perillas (potenciometros)
  Perilla perillaSelector(26);
  Perilla perillaCursor(27);

  // botones
  Boton botonSelector(21);          // 1 clic = minuscula, 2 clics = mayuscula
  Boton botonBorrar(20, false);     // sin doble clic, el borrado es al tiro

  Selector selector;
  Editor editor;

  // que el selector parta en el caracter que indica la perilla
  selector.indice = perillaSelector.posicion(selector.total);

  // dibujo inicial
  pantallaTexto.mostrarCursor(true);
  dibujarTexto(pantallaTexto, editor);

  dibujarSelector(pantallaSelector, selector);
  pantallaSelector.escribirLinea(2, "1 clic: minuscula");
  pantallaSelector.escribirLinea(3, "2 clics: MAYUSCULA");

  while (true) {

    perillaSelector.leer();
    perillaCursor.leer();
    botonSelector.leer();
    botonBorrar.leer();

    // perilla 1: cada caracter tiene su tramo en el potenciometro
    if (perillaSelector.movio) {
      int nuevo = perillaSelector.posicion(selector.total);
      if (nuevo != selector.indice) {
        selector.indice = nuevo;
        dibujarSelector(pantallaSelector, selector);
      }
    }

    // perilla 2: cada posicion del texto tiene su tramo
    if (perillaCursor.movio) {
      int nuevo = perillaCursor.posicion(editor.largo + 1);
      if (nuevo != editor.cursor) {
        editor.cursor = nuevo;
        dibujarTexto(pantallaTexto, editor);
      }
    }

    // boton 2: elegir caracter
    if (botonSelector.clicSimple) {
      editor.insertar(selector.actual());
      dibujarTexto(pantallaTexto, editor);
    }
    if (botonSelector.dobleClic) {
      editor.insertar(Selector::mayuscula(selector.actual()));
      dibujarTexto(pantallaTexto, editor);
    }

    // boton 1: borrar un caracter o todo
    if (botonBorrar.clicSimple) {
      editor.borrar();
      dibujarTexto(pantallaTexto, editor);
    }
    if (botonBorrar.pulsacionLarga) {
      editor.borrarTodo();
      dibujarTexto(pantallaTexto, editor);
    }

    sleep_ms(1);

  }
}