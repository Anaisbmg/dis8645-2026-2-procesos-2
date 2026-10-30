// Pantalla.cpp
// implementaciones de la clase

#include "Pantalla.h"

// bits del modulo I2C (PCF8574)
// P0 = RS, P1 = RW, P2 = E, P3 = luz, P4..P7 = D4..D7
#define LCD_RS   0x01
#define LCD_E    0x04
#define LCD_LUZ  0x08

// constructor
Pantalla::Pantalla(i2c_inst_t* nuevoBus, int nuevaSda, int nuevaScl,
                   uint8_t nuevaDireccion) {

  Pantalla::bus = nuevoBus;
  Pantalla::patitaSda = nuevaSda;
  Pantalla::patitaScl = nuevaScl;
  Pantalla::direccion = nuevaDireccion;

  // iniciar el bus I2C a 400 kHz
  i2c_init(Pantalla::bus, 400 * 1000);
  gpio_set_function(Pantalla::patitaSda, GPIO_FUNC_I2C);
  gpio_set_function(Pantalla::patitaScl, GPIO_FUNC_I2C);
  gpio_pull_up(Pantalla::patitaSda);
  gpio_pull_up(Pantalla::patitaScl);

  Pantalla::iniciar();
}

// metodos
void Pantalla::limpiar() {
  Pantalla::comando(0x01);
  sleep_ms(2);
}

void Pantalla::moverCursor(int fila, int columna) {
  // direcciones donde parte cada fila en un LCD 20x4
  static const uint8_t inicioFila[4] = {0x00, 0x40, 0x14, 0x54};
  Pantalla::comando(0x80 | (inicioFila[fila] + columna));
}

void Pantalla::escribirLinea(int fila, const char* texto) {
  Pantalla::moverCursor(fila, 0);

  // escribe exactamente 20 caracteres
  // si el texto es mas corto rellena con espacios
  bool terminado = false;
  for (int i = 0; i < Pantalla::columnas; i++) {
    if (!terminado && texto[i] == '\0') {
      terminado = true;
    }
    Pantalla::dato(terminado ? ' ' : texto[i]);
  }
}

void Pantalla::mostrarCursor(bool visible) {
  // 0x0F = display + cursor parpadeando, 0x0C = solo display
  Pantalla::comando(visible ? 0x0F : 0x0C);
}

// metodos de bajo nivel
void Pantalla::iniciar() {
  sleep_ms(50);

  // secuencia para pasar el LCD a modo 4 bits
  Pantalla::enviarMitad(0x03, false);
  sleep_ms(5);
  Pantalla::enviarMitad(0x03, false);
  sleep_ms(1);
  Pantalla::enviarMitad(0x03, false);
  sleep_ms(1);
  Pantalla::enviarMitad(0x02, false);
  sleep_ms(1);

  Pantalla::comando(0x28);   // 4 bits, 2 lineas, fuente 5x8
  Pantalla::comando(0x0C);   // display encendido, sin cursor
  Pantalla::comando(0x06);   // el cursor avanza hacia la derecha
  Pantalla::limpiar();
}

void Pantalla::comando(uint8_t valor) {
  Pantalla::enviarByte(valor, false);
}

void Pantalla::dato(uint8_t valor) {
  Pantalla::enviarByte(valor, true);
}

void Pantalla::enviarByte(uint8_t valor, bool esDato) {
  Pantalla::enviarMitad(valor >> 4, esDato);
  Pantalla::enviarMitad(valor & 0x0F, esDato);
}

void Pantalla::enviarMitad(uint8_t mitad, bool esDato) {
  uint8_t valor = (mitad << 4) | LCD_LUZ | (esDato ? LCD_RS : 0);
  Pantalla::pulsarEnable(valor);
}

void Pantalla::pulsarEnable(uint8_t valor) {
  Pantalla::enviarExpansor(valor | LCD_E);
  sleep_us(1);
  Pantalla::enviarExpansor(valor & ~LCD_E);
  sleep_us(50);
}

void Pantalla::enviarExpansor(uint8_t valor) {
  i2c_write_blocking(Pantalla::bus, Pantalla::direccion, &valor, 1, false);
}