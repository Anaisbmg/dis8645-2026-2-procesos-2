#ifndef PERILLA_H
#define PERILLA_H


// Perilla.h
// representa un potenciometro conectado a una entrada analogica (ADC)
// la misma clase sirve para los dos proyectos
//
// atributos de nuestro grupo:  pin, valor, cantidadOpciones
// metodos de nuestro grupo:    leerValor(), seleccionarOpcion()
// instancias de nuestro grupo: perillaEmociones, perillaNavegacion
//
// atributos del grupo 04:      patita, canal, valor, movio, umbral, invertir
// metodos del grupo 04:        muestrear(), leer(), posicion(cantidad)
// instancias del grupo 04:     perillaSelector, perillaCursor


// definir clase Perilla
class Perilla {

  // todo publico
  public:

  // atributos compartidos
  int patita;
  // pin GPIO donde esta conectada (26, 27 o 28)
  int pin;
  // es lo mismo que patita (nombre que usa nuestro documento)
  int valor = 0;
  // ultima lectura guardada (0 a 4095)

  // atributos de nuestro grupo
  int cantidadOpciones = 0;
  // cuantas opciones puede seleccionar (0 = no definida)

  // atributos del grupo 04
  int canal = 0;
  // canal del ADC que corresponde a la patita
  bool movio = false;
  // true si la perilla se movio en esta vuelta
  int umbral = 30;
  // cambio minimo para contar como movimiento
  bool invertir = false;
  // true si la perilla gira al reves

  // constructor: solo la patita es obligatoria
  Perilla(int nuevaPatita, int nuevaCantidadOpciones = 0,
          bool nuevoInvertir = false, int nuevoUmbral = 30);

  // metodos comunes
  int muestrear();
  // lee varias veces y entrega el promedio (quita el ruido)
  int posicion(int cantidad);
  // opcion actual, de 0 a cantidad - 1

  // metodos de nuestro grupo
  int leerValor();
  // lee la perilla y guarda el valor
  int seleccionarOpcion();
  // convierte el valor en una opcion usando cantidadOpciones

  // metodo del grupo 04
  void leer();
  // revisa si la perilla se movio (una vez por vuelta)

};

#endif