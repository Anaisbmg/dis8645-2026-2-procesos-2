# sesion-09a

## apuntes sesión

# Sesión 13-10

En esta clase vimos principalmente **cómo ordenar y representar un circuito en KiCad**, tratando de que el esquemático no sea solamente algo que funcione, sino que también se entienda cuando otra persona lo mira.

# Ordenar antes de conectar

Antes de empezar a tirar cables por todos lados en KiCad, conviene primero poner **todos los componentes que vamos a usar**.

Esto sirve porque así podemos ver:

- Qué componentes tenemos.
- Qué nos falta.
- Qué cosas se relacionan entre sí.
- Cómo conviene ordenar todo antes de empezar a conectar.

Básicamente: **primero ordenar, después conectar**.

Porque si empezamos a tirar cables altiro sin pensar mucho, después queda una telaraña y nadie entiende nada JAJJA.

# El esquemático

El **esquemático** funciona como una especie de mapa del circuito.

Nos muestra:

**qué se conecta con qué**

pero no necesariamente nos dice **dónde estará físicamente cada pieza en el objeto final**.

O sea, si en el esquemático un LED aparece al lado de un botón, eso no significa que en el prototipo final tengan que estar físicamente uno al lado del otro.

El esquemático sirve más para entender la **relación eléctrica entre los componentes**.

# KiCad

En esta sesión trabajamos con **KiCad** para representar nuestro circuito usando símbolos.

Vimos componentes como:

- Raspberry Pi Pico.
- Potenciómetros.
- Pulsadores.
- Resistencias.
- LED.

Cada uno tiene su propio símbolo dentro del esquemático.

## Partes de un símbolo

Cada símbolo contiene distintas informaciones.

Por ejemplo:

### Referencia

La **referencia** sirve para identificar cada componente.

Por ejemplo:

```text
R1
R2
R3
```

La `R` puede indicar que es una resistencia y el número permite diferenciar una de otra.

Entonces, si tenemos varias resistencias, no quedan todas simplemente como "resistencia" JAJJA.

Cada una tiene su propia identificación.

### Valor

El **valor** indica alguna característica importante del componente.

Por ejemplo, en una resistencia podría aparecer:

```text
220 Ω
```
porque ese es el valor de resistencia que tiene.

### Cuerpo del símbolo

Es básicamente **el dibujo que representa al componente** dentro del esquemático.

No necesariamente se ve igual al componente real, porque es una representación gráfica que usamos para entender el circuito.

# OJO con mover las cosas

Hay dos teclas en KiCad que parecen hacer casi lo mismo, pero NO hacen lo mismo.

### `G`

`G` permite **arrastrar un componente manteniendo sus conexiones**.

Entonces, si el componente ya tiene cables conectados y queremos moverlo, los cables se van con él.

### `M`

`M` simplemente **mueve el componente**.

Esto puede hacer que las conexiones no se mantengan de la misma manera.

Entonces:

```text
G → mover manteniendo conexiones
M → mover el componente
```

Hay que tener ojo porque visualmente puede parecer casi lo mismo, pero después podemos dejar algo desconectado sin darnos cuenta.

# Duplicar componentes

También podemos duplicar elementos usando:

```text
Ctrl + D
```

Esto sirve muchísimo cuando necesitamos varios componentes iguales.

Por ejemplo, si ya configuramos una resistencia o un pulsador y necesitamos otro parecido, podemos duplicarlo en vez de crear todo nuevamente desde cero.

Así también podemos conservar algunas de sus propiedades.

# Que el circuito se entienda

Una cosa importante es que el circuito **no solamente tiene que funcionar**.

También tiene que poder entenderse.

La idea es que otra persona pueda abrir nuestro esquemático y seguirlo sin tener que adivinar qué quisimos hacer.

Para eso sirven mucho los **nombres claros y las etiquetas**.

Por ejemplo, si tenemos dos perillas, en vez de dejar algo ambiguo, podemos poner:

```text
perilla_1
perilla_2
```

y cada una puede estar conectada a un pin diferente.

Entonces sabemos exactamente cuál es cuál.

## Orden visual del esquema

También ayuda ordenar el circuito siguiendo una lógica.

Una forma que vimos es:

```text
ENTRADAS → PROCESAMIENTO → SALIDAS
```

O sea:

- **Entradas a la izquierda.**
- **Procesamiento al centro.**
- **Salidas a la derecha.**

Por ejemplo:

```text
botón / perilla → Raspberry Pi Pico → LED
```

Esto hace que podamos leer el circuito casi como una historia: entra información, algo la procesa y después ocurre una respuesta.

Mucho mejor que tener todos los componentes flotando donde sea JAJJA.

# Revisar las conexiones

MUY IMPORTANTE:

**que una línea se vea cerca de un pin NO significa que esté conectada.**

Hay que revisar que el cable llegue realmente al punto de conexión.

Porque podemos mirar el esquema y pensar:

> sí, está conectado

y resulta que hay un espacio microscópico entre el cable y el pin JAJJA.

Entonces siempre conviene revisar bien las uniones.

# Pines que no usamos

No todos los pines de un componente tienen que estar conectados.

Cuando dejamos uno libre a propósito, podemos marcarlo con una **X de no conexión**.

Esa X sirve para decir:

> sí, sé que este pin está suelto, lo dejé así intencionalmente.

Esto también ayuda cuando revisamos el circuito, porque podemos diferenciar entre:

- Algo que olvidamos conectar.
- Algo que decidimos dejar sin conexión.

# Documentar el proyecto

También hablamos de que no todo se documenta necesariamente en un solo diagrama.

Podemos hacer **diagramas de flujo separados** dependiendo de lo que queremos explicar.

Por ejemplo:

### Diagrama del usuario

Podría mostrar lo que hace la persona:

```text
usuario gira la perilla
        ↓
usuario presiona el botón
        ↓
espera una respuesta
```

### Diagrama del hardware

Y otro podría mostrar qué pasa dentro del sistema:

```text
perilla cambia valor
        ↓
Raspberry Pi lee el dato
        ↓
procesa la información
        ↓
LED responde
```

Así podemos separar:

**lo que hace el usuario**

de

**lo que hace la máquina**.

Siento que esto ayuda harto porque si metemos todo en un solo diagrama puede terminar siendo un caos.

# Repositorio e historial

Otra cosa importante es que el repositorio no solamente sirve para guardar los archivos actuales.

También guarda **el historial de nuestro trabajo**.

Eso significa que podemos:

- Ver cambios anteriores.
- Revisar qué modificamos.
- Comparar versiones.
- Volver a una versión anterior si dejamos la embarrada JAJJA.

Entonces el repositorio también funciona como una especie de registro de cómo fue evolucionando el proyecto.


Lo principal de esta clase fue KiCad

```text
poner componentes
+
conectar cables
=
listo
```

También tenemos que pensar en **cómo organizamos y comunicamos ese circuito**.

Primero conviene ordenar los componentes, después hacer las conexiones y finalmente revisar que todo esté realmente unido.

Además, los nombres, etiquetas, símbolos y diagramas ayudan a que otra persona pueda entender lo que hicimos sin que tengamos que estar al lado explicándolo.

Entonces un buen esquemático tiene que ser:

- Claro.
- Ordenado.
- Fácil de seguir.
- Y obviamente estar bien conectado JAJJA.

## encargos

## lectura

En estas páginas entendí más que nada que los modelos físicos servían para hacer visible y mucho más entendible algo tan abstracto como la geometría. Me llamó la atención que no eran solo maquetas para mostrar un resultado, sino que también servían para pensar y experimentar, porque con los modelos de hilos podían ver cómo cambiaban las superficies y las relaciones en el espacio. También aparece cómo estos modelos empiezan a usarse en la enseñanza de arquitectura e ingeniería, casi como una forma de entrenar el ojo y entender cosas que solo con cálculos serían mucho más difíciles de imaginar.

“geometric maquettes shaped a modern architectural intuition of form.”- pág.64

“They were a physical manifestation of mathematical proof.”- pág.66
