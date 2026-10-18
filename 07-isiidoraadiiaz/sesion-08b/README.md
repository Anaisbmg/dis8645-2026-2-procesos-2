# sesion-08b

## apuntes sesión

# Clase 09-10

## Primero, ¿qué queremos hacer?

Partimos retomando las clases Lucecita y Boton que ya teníamos hechas (no tenemos que empezar todo de cero cada vez).

La idea inicial era crear un sistema donde:

- La luz normalmente estuviera apagada.
- Cuando presionamos el botón, empezara a aumentar su intensidad de a poquito.
- Si manteníamos presionado el botón durante más de 2 segundos, la luz empezara a emitir la palabra HOLA en código Morse.

### Umbral de tiempo

El profe habló del **umbral de tiempo presionado**, que es el tiempo mínimo que necesitamos mantener apretado un botón para que suceda algo.

Por ejemplo, un botón del gimnasio que tenemos que mantener presionado durante 2 segundos para activar una máquina.

Esto sirve para evitar que algo se active por accidente.

Lo importante es que antes de empezar a programar tenemos que definir bien qué queremos que suceda.

(IMPORTANTE: ponerse de acuerdo sobre el comportamiento es incluso más importante que escribir el código). 

## Clase Lucecita

Retomamos nuestra clase Lucecita, que tenía:

**Atributos:**
- `patita`: dónde está conectada la luz.
- `prendida`: indica si está encendida o apagada.

**Métodos:**
- `prender()`
- `apagar()`

Pero ahora queríamos que nuestra lucecita pudiera hacer más cosas.

### ¿Qué es rampear?

Rampear significa ir aumentando un valor de a poquito, en vez de pasar inmediatamente del mínimo al máximo.

Por ejemplo, cuando una luz empieza apagada y lentamente va aumentando su brillo.

Para lograrlo necesitábamos un nuevo atributo llamado `intensidad`, que inicialmente valiera cero.

También propusimos un método llamado `rampear()`.

La idea era que cada vez que llamáramos a esa función, la intensidad aumentara en uno.

Pero apareció un problema: si seguimos sumando uno constantemente, el valor puede crecer sin límite.

Entonces necesitamos establecer:

- Una intensidad mínima.
- Una intensidad máxima.
- Una condición para que deje de aumentar cuando llegue al máximo.

Así evitamos que la intensidad siga creciendo infinitamente.

### Tener un valor no significa que la luz cambie

Otro problema era que podíamos aumentar la intensidad dentro del código, pero eso no hacía que el LED realmente cambiara su brillo.

¿Por qué? Porque estábamos modificando una variable interna, pero no enviando ese valor a la luz.

Aquí el profe explicó una diferencia importante:

**Sensores:** leen información del mundo real y la guardan en el programa.

**Actuadores:** reciben información del programa y realizan una acción en el mundo real.

Por eso propuso agregar un método llamado `actualizar()` o `iluminar()`, encargado de comunicar el valor interno de la lucecita hacia el LED.

Entonces, en general, nuestro programa debería seguir este orden:

1. Leer sensores.
2. Tomar decisiones.
3. Emitir una respuesta mediante los actuadores.

(Esta estructura se repite dentro del `while`).

## PWM — Controlar la intensidad

Hasta ahora habíamos utilizado `gpio_put()`, que permite prender o apagar la luz.

Pero si queremos controlar cuánto brilla, necesitamos algo más.

Aquí apareció **PWM (Pulse Width Modulation)**.

PWM significa modulación por ancho de pulso.

Lo que hace es prender y apagar una señal digital muy rápidamente para simular distintos niveles de intensidad.

Por ejemplo, podemos lograr que una luz parezca tener menos brillo, aunque la señal digital solamente pueda estar prendida o apagada.

El profe mostró que en algunas placas Arduino hay patitas especiales que permiten PWM.

Se pueden reconocer por un símbolo parecido a una olita `~`.

IMPORTANTE: no todas las patitas de todas las placas permiten las mismas funciones.

También debemos configurar PWM dentro del código.

Pero como esto empezó a complicarse mucho, decidimos dejar la idea de rampear en pausa y trabajar con algo más sencillo: el código Morse.

(La parte del control de intensidad quedó pendiente en esta clase).

## Código Morse con una lucecita

El código Morse es una forma de representar letras usando puntos y rayas.

Con una luz podemos representar esos puntos y rayas cambiando cuánto tiempo permanece encendida.

- **Punto:** la luz se prende durante un tiempo corto y se apaga.
- **Raya:** la luz se prende durante un tiempo más largo y se apaga.

Entonces podemos usar una sola lucecita para formar letras completas.

### Nuevos métodos

Comenzamos a crear funciones como:

- `morsePunto()`
- `morseRaya()`
- `finLetra()`
- `finPalabra()`

La idea es separar las acciones pequeñas para después combinarlas.

Por ejemplo, no tenemos que escribir las instrucciones para prender y apagar la luz cada vez que queremos hacer una letra.

Basta con llamar a los métodos que ya creamos.

### ¿Qué significa sleep_ms()?

Es una instrucción que hace que el programa espere una cantidad determinada de tiempo.

El tiempo se expresa en milisegundos.

Por ejemplo:

    sleep_ms(200);

Significa esperar 200 milisegundos.

(1000 milisegundos equivalen a un segundo).

Durante la clase se probaron distintos tiempos. Ejemplo un punto de 200 milisegundos y una raya de 1000 milisegundos.

### ¿Cómo se hace un punto?

La lógica es:

1. Prender la luz.
2. Esperar el tiempo correspondiente al punto.
3. Apagar la luz.
4. Esperar antes de la siguiente señal.

Una raya hace exactamente lo mismo, pero permanece prendida durante más tiempo.

También necesitamos pausas para distinguir cuándo termina una letra y cuándo termina una palabra.

Hay funciones para esas pausas, usando tiempos basados en la duración del punto.

## Escribir HOLA en Morse

Para escribir HOLA necesitamos combinar puntos y rayas.

- H: punto punto punto punto.
- O: raya raya raya.
- L: punto raya punto punto.
- A: punto raya.

En Morse se representa así:

    H = ....
    O = ---
    L = .-..
    A = .-

Como ya tenemos métodos para hacer puntos y rayas, podemos llamarlos en el orden correspondiente para formar cada letra.

Y entre las letras agregamos una pausa.

Esto es importante porque estamos construyendo algo complejo a partir de instrucciones pequeñas.

(En vez de escribir el mismo código muchas veces, reutilizamos lo que ya tenemos). yipi

## El botón y sus estados

Después volvimos a trabajar con los botones.

Hasta ahora sabíamos reconocer dos estados:

- Presionado.
- No presionado.

Pero apareció una pregunta importante:

**¿Es lo mismo que un botón esté presionado a que acabe de ser presionado?**

No, son situaciones distintas.

Por ejemplo, imaginemos que queremos que la luz diga HOLA una sola vez cuando apretamos el botón.

Si solamente preguntamos si está presionado, el programa podría repetir HOLA constantemente mientras lo mantenemos apretado.

Pero quizás queremos que lo haga solamente una vez, justo cuando lo presionamos.

Para eso necesitamos reconocer los cambios de estado.

### Estado actual y estado anterior

El profe explicó que podemos guardar dos valores:

- **Estado anterior:** cómo estaba el botón antes.
- **Estado actual:** cómo está ahora.

Antes de actualizar el estado actual, guardamos su valor anterior.

### Rising Edge

El concepto **Rising Edge**, que significa borde ascendente.

Es el momento exacto en que una señal cambia de 0 a 1.

En nuestro botón, sería cuando pasa de no estar presionado a estar presionado.

Lo importante es detectar el cambio, no solamente conocer el estado.

Por ejemplo, si queremos que un sonido se active una vez cuando apretamos un botón, debemos detectar ese momento.

Si mantenemos el botón apretado, no queremos que se active infinitas veces.

### Recién presionado

Para detectar ese cambio podemos agregar un atributo llamado `recienPresionado`.

La lógica sería:

    if (presionadoAnterior == false && presionado == true) {
      recienPresionado = true;
    } else {
      recienPresionado = false;
    }

Esto significa:

Si antes NO estaba presionado y ahora SÍ está presionado, entonces acaba de ser presionado.

Si no se cumplen esas condiciones, no es una nueva pulsación.

Gracias a esto podemos reconocer distintas situaciones:

- Nunca se ha presionado durante las lecturas recientes.
- Acaba de ser presionado.
- Se mantiene presionado.
- Acaba de soltarse.
- Sigue sin presionarse.

El profe explicó que esta lógica será importante para el trabajo final del taller.

## Diseñar el comportamiento del botón

Otra cosa interesante que vimos es que no basta con decir:

"Cuando presiono el botón, la luz dice HOLA".

Tenemos que definir muchas otras cosas.

Por ejemplo:

¿Qué pasa si suelto el botón antes de que termine la palabra?

¿La luz se apaga inmediatamente?

¿Continúa hasta terminar HOLA?

¿Recuerda dónde quedó para continuar después?

Se explicó que todas esas son decisiones de diseño.

Un botón que parece muy simple puede tener muchísimos comportamientos dependiendo de cómo decidamos programarlo.

La opción que se prefirió durante la conversación fue que, una vez iniciada la palabra, terminara de emitirse aunque se soltara el botón.

Los errores también son parte del proceso jejeje

Tuvimos varios errores en Wokwi.

Uno de los problemas fue que el botón estaba conectado de una manera que invertía los valores que esperábamos.

El programa esperaba:

- Sin presionar = 0.
- Presionado = 1.

Pero la conexión hacía lo contrario.

Por eso parecía que el botón estaba siendo presionado apenas empezaba la simulación.

El profe tuvo que revisar las conexiones y corregirlas.

## encargos

## lectura
