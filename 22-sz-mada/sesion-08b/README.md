# sesion-08b

2026.10.09

## apuntes sesión

Debido a que ha llovido torrencialmente durante toda la semana, trabajaremos modalidad remota :skullemoji:

---

Botón LATCH &rarr; se mantiene en el estado en el que se presiona

Encuentro curioso que cuando busco fotos del latching switch, me salen imagenes muy distintas a lo que yo recuerdo haber visto en la clase lol. Aparentemente el nombre del tipo de botón específico que recuerdo es "rocker switch" which makes sense given the shape, pero cabe en la definición del latching switch anyway

![Latching switch](./imagenes/latching-switch.jpg)

&uarr; Latching switch

vs.

![Rocker switch](./imagenes/rocker-switch.jpg)

&uarr; Rocker switch

DIP switch (**D**ual **I**n-line **P**ackage) &rarr; conjunto de interruptores en una sola pieza. Cada switch se puede activar o desactivar independientemente. Size, colour and shape comunica distintos usos

![DIP switch](./imagenes/dip-switch.jpg)

&uarr; DIP switch

Encoder &rarr; parece potenciómetro, pero no lo es (duh), rota infinitamente ya que no tiene un tope físico

![Encoder](./imagenes/encoder.jpg)

&uarr; Encoder

[Wokwi que trabajamos en clase](https://wokwi.com/projects/477413398813766657)

Primero definimos el pseudocódigo i.e. escribir en palabras comunes qué planeamos hacer en el código y el behaviour expected

Aarón agregó el umbral de tiempo presionado (2 seg) por sugerencia de Misaa, en referencia al botón que vio alguien en un gimnasio (see: [isiidoraadiiaz sesion-08a](https://github.com/disenoUDP/dis8645-2026-2-procesos-2/tree/main/07-isiidoraadiiaz/sesion-08a))

La idea es: hay un LED conectado a un botón, el LED no hace nada si no pasa nada. Entre los 0s y 2s de apretado (el botón), el LED prende de a poco; después de los 2s, el LED parpadea "HOLA" en código morse (. . . . / - - - / . - . . / . -)

(Random fun fact about me: en el brazo izquierdo tengo tatuada una frase en código morse :cowboyemoji: , es una referencia cringe a una canción de una banda que me gusta)

Necesitamos 3 versiones, la básica hace que el botón encienda y apague el LED, una que haga la rampa (la luz se prende de a poco), y otra que haga el HOLA en morse

[Video de la clase de Wokwi](https://youtu.be/3rPzC8b9JSg)

---

Algo muy random que aprendí escribiendo mis apuntes, tiendo a usar &rarr; &uarr; &darr; &larr; frecuentemente y siempre se me olvidaba cómo escribir cada flecha porque lo leía como una secuencia extraña de letras, pero en mi último googleo tratando de recordar cada código, noté que simplemente es primera letra dirección + arrow lol. &rarr; es **r**ight **arr**ow, &harr; es **h**orizontal **arr**ow, and so on
