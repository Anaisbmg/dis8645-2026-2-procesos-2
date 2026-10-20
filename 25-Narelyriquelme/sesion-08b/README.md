# sesion-08b

## apuntes sesión

Esta clase fue online por las lluvias fuertes.

---

### Repaso del encargo 08a y componentes

* Se retomó el encargo anterior y se mostraron trabajos de compañeros, sobre todo la parte de los LEDs parpadeando.
* Se miraron fotos de botones, perillas y luces.
* **RK90** → potenciómetros de forma alargada.
* **Encoder** → se parece a una perilla, pero da vueltas sin parar porque no tiene tope físico.
* Idea que quedó dando vueltas: el hardware es una idea o diseño tecnológico hecho cosa física.

---

### Interruptores

**Latch (pulsador con retención)**

* Se queda en el estado en que lo dejaste, aunque lo sueltes.
* Cada pulsación alterna entre prendido y apagado.
* Un `pushbutton` normal, en cambio, solo cuenta mientras lo mantienes apretado.
* También se puede lograr por software, guardando el estado en el microcontrolador.

**Dip switch**

* Varios interruptores chiquititos juntos en una sola carcasa, del porte de un circuito integrado (*dual in-line package*).
* Cada uno se mueve por separado, así que sirve para armar configuraciones binarias y elegir parámetros del hardware.

---

### Código en Wokwi

Lo hicimos entre todos en clase: https://wokwi.com/projects/477413398813766657

* **.h** → lo que el código promete.
* **.cpp** → cómo cumple esa promesa.

**Primer intento**

Partimos con el pseudocódigo, que consistía en medir cuánto tiempo se presiona el botón y compararlo con un umbral de 2 segundos:

* El LED parte siempre apagado.
* Si se presiona menos que el umbral, el LED se va prendiendo gradualmente.
* Si se pasa del umbral, emite "hola" en morse.

Presionar → medir el tiempo → bajo el umbral, LED gradual → sobre el umbral, "hola" en morse

---

### Smalltalk

* Lenguaje donde todo es un objeto y nada más.
* Las clases son los moldes para crear esos objetos.
* Los objetos se hablan entre sí mandándose mensajes, y una máquina virtual se encarga de eso.
* Viene con su propio entorno de desarrollo, lo que permite programar de forma interactiva.

Más info: https://en.wikipedia.org/wiki/Smalltalk

---

### Sistemas de partículas

* Técnica de gráficos por computadora: muchas partículas juntas forman algo difuso (humo, fuego, etc.). Nacen, se mueven, cambian y desaparecen.
* Sirve para simular fenómenos naturales irregulares, y la idea es no ponerle límites a la imaginación.
* Cada partícula es un objeto independiente, como un punto o una forma simple.
* Una clase guarda listas de instancias de otras clases. Con herencia y polimorfismo basta una sola lista para partículas de distintos tipos.
* El **emisor** es la fuente: define cómo parten las partículas (posición, velocidad) y si salen en flujo continuo o variable. Ninguna dura para siempre.

Más info: https://natureofcode.com/particles/

---

## Encargos

## Lectura
