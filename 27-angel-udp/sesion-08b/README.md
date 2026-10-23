# sesion-08b

09-10-2026

## apuntes sesión

Voy a colocar los apuntes que quedaron de esta clase online que no habia puesto anteriormente.

Primero retomamos las clases Lucecita y Botón que habíamos hecho anteriormente para utilizarlas en un nuevo proyecto en Wokwi.

La idea era que al mantener presionado un botón durante 2 segundos, la luz aumentara su intensidad poco a poco y después mostrara la palabra HOLA en código Morse.

Se agregó a la clase Lucecita un valor de intensidad, con un mínimo y un máximo para que no aumentara infinitamente.

Vimos el PWM, que permite controlar la intensidad de una luz prendiendo y apagando rápidamente una señal digital. Como era más complicado, lo dejamos para después.

Trabajamos con el código Morse, donde los puntos y las rayas se diferencian por el tiempo que permanece encendida la luz.

Creamos funciones para Morse punto, Morse raya, fin de letra y fin de palabra, utilizando tiempos de espera con `sleep_ms`.

Probamos el código en Wokwi con una Raspberry Pi Pico y un LED conectado al GP7.

Después agregamos la clase Botón para que la luz funcionara cuando lo presionáramos.

Vimos que un botón puede tener varios estados: no presionado, recién presionado, mantenido presionado y recién soltado.

Para reconocer los cambios se utilizan dos variables, una que guarda el estado anterior y otra el estado actual.

Rising Edge es cuando el botón pasa de estar apagado a encendido, y sirve para activar una acción solo una vez.

En el `main.cpp` utilizamos la función leer y la condición recién presionado para que no se repitiera el mensaje todo el tiempo.

Al probarlo aparecieron algunos errores porque el botón estaba conectado al revés de lo esperado. Se corrigieron las conexiones y finalmente funcionó.

Lo importante es definir bien lo que queremos que haga cada componente antes de programarlo y entender los cambios de estado para utilizarlos en nuestros proyectos.

## encargos

## lectura
