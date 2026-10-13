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



## encargos

## lectura
