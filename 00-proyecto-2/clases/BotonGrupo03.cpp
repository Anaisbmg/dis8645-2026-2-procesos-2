// Boton03.cpp (PROYECTO-02, GRUPO 03)
// implementaciones de la clase hija

#include "Boton03.h"

// constructor
Boton03::Boton03(int nuevoPin, ModoConexion nuevoModo)
    : BotonGenerico(nuevoPin, nuevoModo) {
  Boton03::pin = nuevoPin;
}

// metodos del documento

// true mientras el boton esta apretado
bool Boton03::esta_presionado() {
  return Boton03::estado;
}

// true solo en la vuelta donde se apreto (una accion por pulsacion)
bool Boton03::fue_presionado() {
  return Boton03::seAcabaDePresionar;
}

// true solo en la vuelta donde se solto
bool Boton03::fue_liberado() {
  return Boton03::seAcabaDeSoltar;
}

// metodos de accion

// encendido <-> apagado
void Boton03::alternar() {
  Boton03::activo = !Boton03::activo;
}

// guardar la funcion que se ejecutara al presionar
void Boton03::asignarAccion(void (*nuevaAccion)()) {
  Boton03::accion = nuevaAccion;
}

// ejecutar la accion si hay una asignada
void Boton03::ejecutarAccion() {
  if (Boton03::accion != nullptr) {
    Boton03::accion();
  }
}

// ganchos de la base

// la base avisa justo cuando se aprieta
void Boton03::alPresionar() {
  Boton03::estado = true;
  if (Boton03::modoAlternar) {
    Boton03::alternar();
  }
  Boton03::ejecutarAccion();
}

// la base avisa justo cuando se suelta
void Boton03::alSoltar() {
  Boton03::estado = false;
}
