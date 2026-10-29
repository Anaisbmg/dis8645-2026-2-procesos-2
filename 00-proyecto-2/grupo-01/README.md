# [placeholder para el nombre ayudaaa]

## concepto

## clases

## concepto

Se plantea que el sonido de un computador está condicionado por la tecnología de su época, desde los chips de síntesis que generaban melodías y efectos electrónicos hasta la incorporación de audio digital y música grabada.

A partir de esta exploración, surge la pregunta: ¿cómo ha evolucionado el sonido de los videojuegos a medida que cambian las capacidades tecnológicas de los computadores? El proyecto busca reconocer estas transformaciones y comprender cómo las características sonoras permiten identificar distintas etapas en la historia de estas máquinas.

La evolución del sonido y la música en los videojuegos japoneses ha transitado desde los simples tonos monofónicos de los arcades y consolas de 8 bits hasta complejas bandas sonoras dinámicas e integradas con tecnología binaural y orquestal.

Fases de la evolución del sonido en Japón

• Era de 8 bits y 16 bits (Años 80 - Principios de los 90): Limitada por chips de sonido de canales reducidos (como el chip PSG o el chip de FM de Yamaha en sistemas como la NES, MSX o Mega Drive/Genesis). Compositores como Koji Kondo (en Super Mario o The Legend of Zelda) y Nobuo Uematsu (en Final Fantasy) crearon melodías altamente pegajosas que definieron la identidad del chip chiptune debido a las restricciones técnicas de la memoria.

• Era del CD-ROM y 32 bits (Mediados de los 90): Con la llegada de soportes como la PlayStation o la Sega Saturn, se dio el salto al audio grabado (pistas en formato Red Book CD o MIDI avanzado), permitiendo incorporar instrumentos acústicos reales, coros y arreglos orquestales más emotivos.

Era moderna y el sonido interactivo (Siglo XXI - Presente): La música y los efectos dejaron de ser simples archivos lineales para volverse adaptativos y dinámicos, reaccionando en tiempo real a las acciones del jugador, la exploración o el combate. Además, géneros como el jazz, la música electrónica y fusiones culturales pasaron a ser sellos distintivos en sagas como Persona o Sonic the Hedgehog

## clases

### integrantes

Bianka Vilchez

Dayana Pañitrur

Camila Ramirez

### Inspiración

Seleccionar un computador personal creado entre 1980 y 2010 y desarrollar un tributo a partir de una de sus características más representativas.

El proyecto consiste en rendir tributo a un computador personal mediante la exploración de sus características sonoras y funcionales. A través de una propuesta interactiva, se busca representar sus funciones y procesos mediante sonidos percusivos, utilizando ritmos, frecuencias y secuencias que permitan identificar sus distintos modos de funcionamiento.

El sonido de un computador está condicionado por la época en la que fue desarrollado, ya que responde a las posibilidades tecnológicas, las necesidades funcionales y el contexto cultural de su tiempo.

Por ejemplo, ¿suena igual un computador de los años 80 que uno de los años 2000? ¿Qué diferencias existen entre sus sonidos y qué nos dicen sobre la evolución de estas máquinas? Se plantea que los sonidos de un computador permiten reconocer aspectos de su época, desde sus limitaciones técnicas hasta las formas en que las personas se relacionaban con la tecnología.

Sharp X68000

El proyecto consiste en un dispositivo sonoro inspirado en las configuraciones y el sistema del computador Sharp X68000. La interacción se realizará mediante dos botones y dos perillas, cada uno con una función específica para seleccionar, reproducir y controlar los sonidos.

### Controles e interacciones

El encoder rotatorio cumple dos funciones en un solo componente: funciona como **perilla** al girarlo y como **botón** al presionarlo, ya que incluye un pulsador integrado en su eje.

| Control | Componente | Especificación | Acción |
| --- | --- | --- | --- |
| Encoder (perilla): giro horario | Encoder rotatorio con pulsador | Tipo KY-040 o similar* | Avanza al siguiente sonido. |
| Encoder (perilla): giro antihorario | Encoder rotatorio con pulsador | Tipo KY-040 o similar* | Retrocede al sonido anterior. |
| Encoder (botón): pulsación | Encoder rotatorio con pulsador | Tipo KY-040 o similar* | Reproduce el sonido seleccionado. |
| Potenciómetro (perilla) | Potenciómetro | 10 kΩ lineal* | Regula el volumen general en un rango de 0 a 100. |
| Botón Loop: primera pulsación | Botón pulsador | Momentáneo, 12 × 12 mm* | Activa la repetición continua del sonido. |
| Botón Loop: segunda pulsación | Botón pulsador | Momentáneo, 12 × 12 mm* | Desactiva la repetición continua del sonido. |
| Cinco lucecitas LED | 5 LED + 5 resistencias | LED 5 mm*, resistencias 220–330 Ω* | Indican cuál de los cinco sonidos está seleccionado. |

### Experiencia de uso

1. **Encender el dispositivo:** el sistema se inicia y queda preparado para seleccionar un sonido.
2. **Seleccionar un sonido:** la persona gira el encoder en sentido horario o antihorario para recorrer los cinco sonidos. La lucecita correspondiente indica cuál está seleccionado.
3. **Reproducir el sonido:** la persona presiona el encoder para escuchar el sonido seleccionado.
4. **Regular el volumen:** gira el potenciómetro para ajustar el volumen general del dispositivo, dentro de un rango de 0 a 100.
5. **Activar el loop:** presiona el botón LOOP una vez para que el sonido se repita continuamente.
6. **Desactivar el loop:** presiona nuevamente el botón LOOP para desactivar la repetición.
7. **Cambiar de sonido:** gira el encoder para seleccionar otro sonido y presiónalo para reproducirlo. Si el sonido anterior estaba en loop, el sistema debe gestionar el cambio según la lógica definida para la reproducción.
8. **Explorar los cinco sonidos:** la persona puede recorrer el menú de forma continua. Después del quinto sonido, el encoder vuelve al primero; en sentido contrario, desde el primero pasa al quinto.

### Archivos

main.cpp

Boton.h + Boton.cpp

Perilla.h + Perilla.cpp

Sonido.h + Sonido.cpp

Lucecita.h + Lucecita.cpp

ampli.h + ampli.cpp

## seudo-código

1. Inicia la máquina

2. Se define los parametros inciales de la máquina (en que sonido incia)

3.

### class Boton

Como grupo nos corresponde realizar la clase Boton, el cuál debe funcionar tanto para lo que hagamos nosotras en nuestro proyecto, como para lo que haga el grupo 07 para el suyo.

Licencia
Este código es obra de Bianka Vilchez, Camila Ramirez y Dayana Pañitrur (2026).
Se distribuye bajo la licencia [Creative Commons Atribución-CompartirIgual 4.0 Internacional](http://creativecommons.org/licenses/by-sa/4.0/).

#### Boton.h

En el archivo .h definimos todo, declaramos todo, prometemos las cosas que hará el botón, el cómo lo hará lo escribiremos en el archivo .cpp

El nombre de nuestra clases es **BotonGrupo1**

Algo importante que debemos integrar en nuestro archivo .h son:

- La biblioteca de la Rapberry Pi Pico para poder programarla
- Biblioteca del GPIO, para integrar la conexión física de los pines de la Raspi

Hacer el código `public` hará que cualquier persona pueda ver, usar o modificar nuestra clase Boton

modoSwitch

| anterior | actual | resultado |
| :------: | :----: | :-------: |
| 0        | 0      |  0        |
| 1        | 0      | 1         |
| 1        | 1      | 0         |
| 0        | 1      | 1         |

XOR

Una u otra, pero no ambos

Cuando el anterior **o** el actual cambien de estado, el `modoSwitch` lo hará

#### Boton.cpp

![Diagrama Botón](./imagenes/boton-leer-v02.png)

![Diagrama Botón](./imagenes/boton-doble-click.png)

![Diagrama Botón](./imagenes/boton-switch.png)

![Diagrama Botón](./imagenes/boton-modo-borrar.png)

### class Led


### class Ampli

Se preparó

```cpp

#ifndef AMPLI_H
#define AMPLI_H

#include "hardware/adc.h"

class Ampli {

  public:

  // --atributos--
  // a que pin se conecta el BCLK
  // Bit CLocK  
  int pinReloj;

  // a que pin se conecta LRC
  // debe ir consecutivo a reloj
  int pinLRC = pinReloj + 1 ;

  // a que pin se conecta el DIN
  // Serial Audio Data 
  int pinDatos;
  
  bool sonando = false; 

  int volumen = 50;
  int frecuencia = 11025;

 // variable que enlaza al listado de sonidos que se carguen eventualmente
 // cuenta desde 0
  int sonidoActual = -1;

 // -- constructor --
 Ampli(int pinReloj, int pinDatos);

 // --metodos--
 // realiza el proceso de reproducir audio
 // reproduce sonidoActual
 void reproducir();

 // el audio debe reproducirse de manera ciclica
 //reproduce sonidoActual
 void reproducirLoop();

 // estipula como se regula el volumen
 // utiliza valores de 0 a 100
 void controlVolumen(); 
};

#endif

```

<br>

```cpp

#include "Ampli.h"

//constructor 
Ampli::Ampli(int pinReloj, int pinDatos) {

  pinReloj = nuevoPinReloj;
  pinDatos = nuevoPinDatos;

   // inicia el ampli MAX98357A pero sin reproducir ningún sonido 
   //
}

// Inicia la reproducción de audio
// esta funciona con la variable sonidoActual
// tiene inicio y fin 
void Ampli::reproducir(){
}

// A diferencia de reproducir()
// Inicia el sonido de modo ciclico
// funciona con la variable sonidoActual
void Ampli::reproducirLoop(){ 
}

// Define como se controla el volumen
// se trabaja con valores de 0 a 100
void Ampli::controlVolumen(){

}

```
