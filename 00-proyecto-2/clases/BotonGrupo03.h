#ifndef BOTON03_H
#define BOTON03_H

#include "BotonGenerico.h"


// Boton03.h
// PROYECTO-02, GRUPO 03: maquina de emociones
// clase hija de BotonGenerico (Clase 01 del documento)
//
// atributos del documento: pin, estado, funcion
// metodos del documento:   esta_presionado(), fue_presionado()
//
// instancias (se crean en el main):
//   boton_encendido            enciende y apaga la maquina
//   boton_salto                hace saltar al personaje del minijuego


// definir clase Boton03 (hereda todo lo de BotonGenerico)
class Boton03 : public BotonGenerico {

  // todo publico
  public:

  // atributos del documento
  int pin;                            
  // pin GPIO donde esta conectado (= patita)
  bool estado = false;                
  // true = presionado, false = liberado
  int funcion = 0;                    
  // numero que identifica la accion asignada
                                      
  // (cada grupo define los suyos en su main)

  // atributos para encender / apagar y para acciones
  bool modoAlternar = false;          
  // true = cada pulsacion cambia 'activo'
  bool activo = false;                
  // encendido / apagado (solo con modoAlternar)
  void (*accion)() = nullptr;         
  // funcion que se ejecuta sola al presionar (opcional)


  // constructor
  Boton03(int nuevoPin, ModoConexion nuevoModo = PULL_UP_INTERNO);

  // metodos del documento
  bool esta_presionado();             
  // true mientras esta apretado
  bool fue_presionado();              
  // true UNA sola vez por pulsacion
  bool fue_liberado();                
  // true UNA sola vez al soltar

  // metodos de accion
  void alternar();                    
  // cambia 'activo' (encendido <-> apagado)
  void asignarAccion(void (*nuevaAccion)());
  void ejecutarAccion();

  // sobreescribe los ganchos de la base
  void alPresionar() override;
  void alSoltar() override;

};

#endif
