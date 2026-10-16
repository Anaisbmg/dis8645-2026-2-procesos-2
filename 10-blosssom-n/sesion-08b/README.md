# sesion-08b

## apuntes sesión


# sesion-08b

## apuntes sesión

La clase fue online por la lluvia. Partimos revisando las fotos de botones, perillas y luces del encargo anterior, y los ejercicios para hacer parpadear el LED en Wokwi.

Vimos el latch, que mantiene su estado después de dejar de presionarlo. Es como un botón que recuerda si quedó prendido o apagado. Ese comportamiento también se puede programar con un pulsador común.

También apareció el DIP switch, que es un conjunto de interruptores chiquititos dentro de una misma pieza. Cada uno se puede activar por separado. El tamaño, la forma y los colores de estos componentes también comunican para qué sirven.

Antes de programar, hay que definir qué queremos que pase. Podemos escribir los pasos con comentarios o pseudocódigo, usando palabras simples (primero entender la idea y después ver cómo escribirla).

Para el botón pensamos distintos estados: no está presionado, está siendo presionado y se acaba de soltar. También importa cuánto tiempo lo mantenemos apretado, porque eso puede cambiar lo que hace.

La idea inicial del ejercicio era que la luz estuviera apagada y aumentara su intensidad al mantener presionado el botón. Al superar los dos segundos, diría “hola” en código morse.

Aumentar la intensidad de a poquito se llamó rampear. Si vamos sumando de uno en uno, necesitamos poner un límite para que el número no siga subiendo para siempre.

Después el ejercicio se enfocó en el morse: un punto es un encendido corto y una raya es uno más largo. Combinándolos y dejando pausas podemos formar letras.

Para recordar: en .h declaramos lo que puede hacer la clase, como sus promesas, y en .cpp escribimos cómo lo hace. En main.cpp creamos los objetos y usamos sus métodos. También usamos sleep_ms() para esperar un tiempo en milisegundos.

Me llamó la atención que con un botón podemos hacer más cosas que prender y apagar, dependiendo de cuánto dura la presión y cuándo cambia de estado.

me cuesta un poco prestar atención cuando hay clases online, porque en mi casa tengo tantas cosas que me distraen y no estoy medicada!! pero lo intenté


## encargos

## lectura
