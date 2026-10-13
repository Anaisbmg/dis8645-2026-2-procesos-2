# sesion-08b

## apuntes sesión

Al comienzo de la clase revisamos el encargo de imágenes que hicieron algunos compañeros y después retomamos el ejercicio de hacer parpadear una lucecita utilizando un botón y una perilla en Wokwi. 

### -. Multiplexer

+ Un multiplexer es un componente que permite recibir varias señales de entrada y seleccionar cuál de ellas se envía a una única salida.

+ En otras palabras, permite trabajar con varias señales utilizando una misma salida, dependiendo de cuál se quiera seleccionar.

### -. Programación en Wokwi

Seguimos trabajando con la programación de la lucecita, agregando la posibilidad de controlar su intensidad.

+ Por ejemplo:

Lucecita::intensidad = Lucecita::intensidad + 1;

Esto significa que la intensidad aumenta de uno en uno. Sin embargo, necesitamos establecer un límite para que el valor no siga aumentando indefinidamente y se mantenga dentro del rango permitido.

También apareció el método luz.rampear, relacionado con la idea de hacer que la intensidad de la luz aumente o disminuya progresivamente, en vez de cambiar de golpe.

### -.Estados del botón

También hablamos de cómo podemos representar diferentes estados a partir de la información que recibimos de un botón

Por ejemplo, podemos distinguir entre:

+ El botón está presionado

+ El botón no está presionado

+ El botón sigue presionado

La idea es que, aunque un botón tenga dos estados básicos —presionado y no presionado—, podemos observar cómo cambia su estado a lo largo del tiempo para reconocer situaciones diferentes.

Esto permite crear comportamientos más complejos a partir de información sencilla, combinando estados y condiciones dentro del código

+ Latch

Es un interruptor que recuerda su estado. Se presiona una vez para activarlo y otra vez para desactivarlo, sin necesidad de mantenerlo presionado. Este comportamiento también se puede programar con un botón común.

+ DIP Switch

Es un conjunto de pequeños interruptores dentro de un mismo encapsulado, que se pueden activar o desactivar de forma independiente.

### Tamaño y función

El tamaño y la forma de un componente pueden relacionarse con su función. Los colores también comunican información, por ejemplo, rojo para alertas, verde para indicar que todo está bien y azul para señalar que algo está encendido o tiene corriente.

### Potenciómetro con switch

Permite regular una variable y encender o apagar un dispositivo con el mismo componente. Un ejemplo es el Otamatone, que se enciende al subir el volumen.

### Componentes y conceptos

Multiplexer (MUX): recibe varias señales y selecciona una para enviarla a una única salida. El demultiplexer hace lo contrario.

CD4051: permite seleccionar entre 8 canales utilizando 3 entradas selectoras.

MAX7219: sirve para controlar matrices de LED o displays.

PWM: permite regular la intensidad de una luz variando el tiempo que la señal permanece encendida y apagada.

PWM slice: es parte del hardware que genera señales PWM en microcontroladores como el RP2040.

Rising edge: es el cambio de una señal de 0 a 1, que permite detectar eventos como la activación de un botón.

CD4016: es un circuito integrado con cuatro interruptores electrónicos independientes, que permiten conectar o desconectar señales.

## encargos

## lectura
