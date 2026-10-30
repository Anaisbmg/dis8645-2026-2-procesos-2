// Boton.cpp (PROYECTO-02)
// implementaciones de la clase
// mismas 3 partes que el header:
//   PARTE 1: BASE, PARTE 2: GRUPO 04, PARTE 3: GRUPO 03

#include "Boton.h"

// funcion chiquitita para saber la hora en milisegundos
static uint32_t ahora() {
  return to_ms_since_boot(get_absolute_time());
}


// =====================================================
// PARTE 1: BASE (la usan los dos grupos)
// =====================================================

// constructor
Boton::Boton(int nuevaPatita, ModoConexion nuevoModo) {

  // guardar los valores
  Boton::patita = nuevaPatita;
  Boton::modo = nuevoModo;

  // grupo 03: el documento lo llama 'pin'
  Boton::pin = nuevaPatita;

  // inicializar patita
  gpio_init(Boton::patita);
  // la patita es entrada
  gpio_set_dir(Boton::patita, GPIO_IN);

  // segun como este conectado, configuramos las resistencias
  // y decidimos si apretado es 1 o es 0
  if (Boton::modo == PULL_UP_INTERNO) {
    gpio_pull_up(Boton::patita);
    Boton::activoEnAlto = false;
  }
  else if (Boton::modo == PULL_DOWN_INTERNO) {
    gpio_pull_down(Boton::patita);
    Boton::activoEnAlto = true;
  }
  else if (Boton::modo == EXTERNO_ACTIVO_ALTO) {
    gpio_disable_pulls(Boton::patita);
    Boton::activoEnAlto = true;
  }
  else {
    gpio_disable_pulls(Boton::patita);
    Boton::activoEnAlto = false;
  }
}

void Boton::leer() {

  // borrar los eventos de la vuelta anterior
  Boton::seAcabaDePresionar = false;
  Boton::seAcabaDeSoltar = false;
  Boton::clicSimple = false;
  Boton::dobleClic = false;
  Boton::tripleClic = false;
  Boton::pulsacionLarga = false;
  Boton::clicsDetectados = 0;

  uint32_t t = ahora();

  // leer boton (true = apretado, sin importar como este conectado)
  bool lectura = (gpio_get(Boton::patita) == Boton::activoEnAlto);

  // antirrebote: solo creemos el cambio si se mantiene estable
  if (lectura != Boton::ultimaLectura) {
    Boton::ultimaLectura = lectura;
    Boton::ultimoCambio = t;
  }

  if ((t - Boton::ultimoCambio) >= (uint32_t)Boton::tiempoAntirrebote
      && lectura != Boton::presionado) {
    if (lectura) {
      Boton::presionar();
    }
    else {
      Boton::soltar();
    }
  }

  if (Boton::presionado) {
    // calcular cuanto rato lleva presionado
    Boton::duracionPresionado = t - Boton::inicioPresion;

    if (!Boton::largoDisparado
        && Boton::duracionPresionado >= Boton::tiempoLargo) {
      // primera vez que se cumple el tiempo largo
      Boton::largoDisparado = true;
      Boton::pulsacionLarga = true;
      Boton::vecesLargo = 1;
      Boton::ultimaRepeticion = t;
      Boton::clics = 0;
    }
    else if (Boton::largoDisparado && Boton::repetirLargo
             && (t - Boton::ultimaRepeticion)
                >= (uint32_t)Boton::intervaloRepeticion) {
      // sigue apretado y se pidio repeticion
      Boton::pulsacionLarga = true;
      Boton::vecesLargo++;
      Boton::ultimaRepeticion = t;
    }
  }
  else if (Boton::clics > 0
           && (t - Boton::ultimoSoltado)
              >= (uint32_t)Boton::ventanaClics) {
    // paso la ventana y nadie mas apreto: se cierra la secuencia de clics
    Boton::emitirClics(Boton::clics);
    Boton::clics = 0;
  }
}

// metodos
void Boton::presionar() {
  Boton::presionado = true;
  Boton::seAcabaDePresionar = true;
  Boton::inicioPresion = ahora();
  Boton::largoDisparado = false;
  Boton::vecesLargo = 0;

  // grupo 03: estado y acciones automaticas al presionar
  Boton::estado = true;
  if (Boton::modoAlternar) {
    Boton::alternar();
  }
  Boton::ejecutarAccion();
}

void Boton::soltar() {
  Boton::presionado = false;
  Boton::duracionPresionado = 0;
  Boton::seAcabaDeSoltar = true;

  // grupo 03: estado liberado
  Boton::estado = false;

  // si fue pulsacion larga no cuenta como clic
  if (Boton::largoDisparado) {
    return;
  }

  // grupo 04: con permitirDoble en false el maximo es 1 clic
  int maximo = Boton::permitirDoble ? Boton::clicsMaximos : 1;

  // sin multiclic: el clic sale al tiro
  if (maximo <= 1) {
    Boton::emitirClics(1);
    return;
  }

  Boton::clics++;
  Boton::ultimoSoltado = ahora();

  // se llego al maximo de clics: no hace falta esperar mas
  if (Boton::clics >= maximo) {
    Boton::emitirClics(Boton::clics);
    Boton::clics = 0;
  }
}

// avisa cuantos clics tuvo la secuencia
void Boton::emitirClics(int cantidad) {
  Boton::clicsDetectados = cantidad;
  Boton::clicSimple = (cantidad == 1);
  Boton::dobleClic = (cantidad == 2);
  Boton::tripleClic = (cantidad == 3);
}


// =====================================================
// PARTE 2: GRUPO 04 - MAQUINA MULTITAP
// =====================================================

// constructor: Boton(pin, permitirDoble)
// usa pull-up interno (boton a GND), igual que el proyecto original
Boton::Boton(int nuevaPatita, bool nuevoPermitirDoble)
    : Boton(nuevaPatita, PULL_UP_INTERNO) {
  Boton::permitirDoble = nuevoPermitirDoble;
}


// =====================================================
// PARTE 3: GRUPO 03 - MAQUINA DE EMOCIONES
// =====================================================

// true mientras el boton esta apretado
bool Boton::esta_presionado() {
  return Boton::estado;
}

// true solo en la vuelta donde se apreto (una accion por pulsacion)
bool Boton::fue_presionado() {
  return Boton::seAcabaDePresionar;
}

// true solo en la vuelta donde se solto
bool Boton::fue_liberado() {
  return Boton::seAcabaDeSoltar;
}

// encendido <-> apagado
void Boton::alternar() {
  Boton::activo = !Boton::activo;
}

// guardar la funcion que se ejecutara al presionar
void Boton::asignarAccion(void (*nuevaAccion)()) {
  Boton::accion = nuevaAccion;
}

// ejecutar la accion si hay una asignada
void Boton::ejecutarAccion() {
  if (Boton::accion != nullptr) {
    Boton::accion();
  }
}
