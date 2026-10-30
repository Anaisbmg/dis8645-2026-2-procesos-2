#ifndef BOTON_H
#define BOTON_H

// para GPIO y para el tiempo
#include "pico/stdlib.h"
#include "hardware/gpio.h"


// Boton.h
// PROYECTO-02
// UNA sola clase Boton que usan los dos grupos.
// el archivo esta dividido en 3 partes:
//
//   PARTE 1: BASE      lo que usan los dos grupos
//   PARTE 2: GRUPO 04  maquina multitap (teclado con 2 perillas)
//   PARTE 3: GRUPO 03  maquina de emociones
//
// cada grupo cambia los atributos desde su main.cpp,
// sin editar este archivo ni Boton.cpp
//
// ---------------------------------------------------------
// QUE USA CADA GRUPO
// ---------------------------------------------------------
// GRUPO 04 (multitap)
//   atributos: patita, presionado, duracionPresionado, permitirDoble
//   eventos:   clicSimple, dobleClic, pulsacionLarga
//   metodos:   Boton(pin, permitirDoble), leer()
//   instancias: botonSelector, botonBorrar
//
// GRUPO 03 (emociones)
//   atributos: pin, estado, funcion, modoAlternar, activo, accion
//   metodos:   Boton(pin), esta_presionado(), fue_presionado(),
//              fue_liberado(), alternar(), asignarAccion(), ejecutarAccion()
//   instancias: boton_encendido, boton_salto
// ---------------------------------------------------------


// como esta conectado el boton
enum ModoConexion {
  PULL_UP_INTERNO,        // boton entre el pin y GND, usa la resistencia interna
  PULL_DOWN_INTERNO,      // boton entre el pin y 3V3, usa la resistencia interna
  EXTERNO_ACTIVO_ALTO,    // resistencia externa a GND, boton a 3V3 (apretado = 1)
  EXTERNO_ACTIVO_BAJO     // resistencia externa a 3V3, boton a GND (apretado = 0)
};


// definir clase Boton
class Boton {

  // todo publico
  // nada de andar privatizando
  public:

  // =====================================================
  // PARTE 1: BASE (la usan los dos grupos)
  // =====================================================

  // ---------- atributos basicos ----------
  int patita;
  ModoConexion modo;
  bool activoEnAlto;                  // true si apretado lee 1
  bool presionado = false;
  int duracionPresionado = 0;         // ms que lleva presionado

  // ---------- eventos ----------
  // son true SOLO en la vuelta del loop donde ocurren
  bool seAcabaDePresionar = false;
  bool seAcabaDeSoltar = false;
  bool clicSimple = false;
  bool dobleClic = false;
  bool tripleClic = false;
  bool pulsacionLarga = false;
  int clicsDetectados = 0;            // cuantos clics tuvo la secuencia (0 si no hubo)
  int vecesLargo = 0;                 // cuantas veces se disparo la pulsacion larga

  // ---------- configuracion (se puede cambiar desde afuera) ----------
  int tiempoAntirrebote = 20;         // ms que debe estar estable la lectura
  int tiempoLargo = 1000;             // ms para contar como pulsacion larga
  int ventanaClics = 300;             // ms maximos entre un clic y el siguiente
  int clicsMaximos = 2;               // 1 = sin multiclic (el clic sale al tiro)
  bool repetirLargo = false;          // true = la pulsacion larga se repite
  int intervaloRepeticion = 200;      // ms entre cada repeticion

  // ---------- atributos internos ----------
  bool ultimaLectura = false;
  bool largoDisparado = false;
  int clics = 0;
  uint32_t ultimoCambio = 0;
  uint32_t inicioPresion = 0;
  uint32_t ultimoSoltado = 0;
  uint32_t ultimaRepeticion = 0;

  // ---------- constructor ----------
  Boton(int nuevaPatita, ModoConexion nuevoModo = PULL_UP_INTERNO);

  // ---------- metodos ----------
  void leer();
  void presionar();
  void soltar();
  void emitirClics(int cantidad);


  // =====================================================
  // PARTE 2: GRUPO 04 - MAQUINA MULTITAP
  // =====================================================
  //
  // INSTANCIAS (se crean en el main):
  //   botonSelector(21)          1 clic = minuscula, 2 clics = MAYUSCULA
  //   botonBorrar(20, false)     1 clic = borrar un caracter,
  //                              mantener apretado = borrar todo
  //
  // ATRIBUTOS de este grupo:
  bool permitirDoble = true;          // false = el clic simple sale al tiro
                                      // (el boton de borrar no espera un 2do clic)
  //
  // CONSTRUCTOR de este grupo:
  Boton(int nuevaPatita, bool nuevoPermitirDoble);
  //
  // METODOS que usa: leer() y los eventos de la BASE
  // (clicSimple, dobleClic, pulsacionLarga)


  // =====================================================
  // PARTE 3: GRUPO 03 - MAQUINA DE EMOCIONES
  // =====================================================
  //
  // INSTANCIAS (se crean en el main):
  //   boton_encendido            enciende y apaga la maquina
  //   boton_salto                hace saltar al personaje del minijuego
  //
  // ATRIBUTOS de este grupo (los pide el documento):
  int pin;                            // pin GPIO donde esta conectado (= patita)
  bool estado = false;                // true = presionado, false = liberado
  int funcion = 0;                    // numero que identifica la accion asignada
                                      // (cada grupo define los suyos en su main)
  bool modoAlternar = false;          // true = cada pulsacion cambia 'activo'
  bool activo = false;                // encendido / apagado (solo con modoAlternar)
  void (*accion)() = nullptr;         // funcion que se ejecuta sola al presionar (opcional)
  //
  // METODOS de este grupo:
  bool esta_presionado();             // true mientras esta apretado
  bool fue_presionado();              // true UNA sola vez por pulsacion
  bool fue_liberado();                // true UNA sola vez al soltar
  void alternar();                    // cambia 'activo' (encendido <-> apagado)
  void asignarAccion(void (*nuevaAccion)());
  void ejecutarAccion();

};

#endif
