---
title: pseudo

---

## pseudo.h

### Contexto del proyecto:

Nuestro proyecto consiste en la creación de una máquina computacional interactiva, analógica y digital, inspirada en diversas máquinas computacionales de entretenimiento, como la **Game Boy**, **Guitar Hero** y **DJ Hero**.

Es así como nace **(nombre de nuestre hijee)**, una máquina de entretenimiento de bolsillo compuesta por dos botones y dos perillas. Funciona de la siguiente manera:

El juego tiene cuatro caminos por los cuales bajan constantemente luces de diversos colores, como en el juego *Piano Tiles*. La usuaria debe desplazarse entre estos rieles y hacer *match* con el color de la luz que va bajando para continuar jugando. Si no hace *match* con el color correspondiente en el camino equivalente, pierde.

Nuestra inspiración para la construcción de la carcasa nace principalmente de la **Game Boy**, una videoconsola portátil de 8 bits desarrollada y fabricada por Nintendo, lanzada por primera vez en Japón el 21 de abril de 1989 y que popularizó mundialmente los videojuegos de bolsillo.

### Lista de materiales:

nuestro proyecto será un juego de ritmo el cual tendrá los siguientes componentes:

+ Matriz LED RGB 8×8 con WS2812B – 64 píxeles direccionables
+ Botones pulsadores (2)
+ Perillas (2)
+ Switch
+ Raspberry Pi Pico 2W
+ Bocina(?)
+ MAX98357A
+ Parlante 30 mm (3 cm) 4 Ω 3 W

### pseudocódigo de los componentes:

## switch

- Switch: Encendido y apagado del juego
    - para encender la pantalla, posición 1
    - para apagar la pantalla, posición 0
    

## botones

boton publico (todo publico, no olvidar)

bool presionado
int duracionPresionado
int patita

boton lee
boton presiona
boton suelta

- Botón 1: Cambio de nivel del juego (nivel 1, 2 y 3)
    - tres estados posibles: presión 1, presión 2, presión 3. voler a estado 1.
    - en presión 1, selección de nivel de dificutlad 1
    - en presión 2, selección de nivel de dificultad 2
    - en presión 3, selección de nivel de dificultad 3

- Botón 2: Selección del led posicionado
    - al presionar el botón en la casilla correcta, se pone el led en verde
    - al presionar el botón en la casilla incorrecta, se pone el led en rojo

## perillas

perilla publica
    
- Perilla 1: Cambio de velocidad del nivel
    - resolución de la perilla en raspi es de 0-4095, se usará este espectro para controlar la velocidad en la que caen los rectángulos que debes atrapar en la fila inferior de la pantalla. 0 es la velocidad más lenta mientras que 4095 es la más rápida.
    
- Perilla 2: Recorrido de la posición del led 
    - resolución de la perilla en raspi es de 0-4095, se delimitará cuatro posiciones posibles para poder moverte con este dentro de la pantalla.
        - posición 1, rectángulo en extremo inferior derecho
        - posición 2, rectángulo en mitad derecha inferior
        - posición 3, rectángulo en mitad izquierda inferior
        - posición 4, rectángulo en extremo inferior izquierdo.
    

