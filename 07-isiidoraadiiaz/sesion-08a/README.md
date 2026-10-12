# sesion-08a

## apuntes sesión
# Clase 06-10

## Constructor

Volvimos a hablar del **constructor**.

El constructor lo usamos para **crear objetos a través de una clase** y darle los valores iniciales que necesita ese objeto.

Una forma fácil de reconocerlo es que, cuando vemos algo dentro de una clase que tiene **exactamente el mismo nombre de la clase**, ese es el constructor.

Por ejemplo, si tenemos:

```cpp
class Lucecita {
public:

    Lucecita() {
        
    }
};
```

`Lucecita()` es el **constructor**, porque tiene el mismo nombre que la clase.


# Clase `Lucecita`

Vimos como ejemplo una clase llamada `Lucecita`.

Primero tenemos que pensar **qué cosas necesitamos saber sobre una lucecita**.

Podrían ser:

- Si está encendida o apagada.
- Cuánto brillo tiene.
- Si parpadea o no.

Por ejemplo:

```cpp
class Lucecita {
public:

    bool encendido;
    int brillo;
    bool parpadea;

};
```

### `encendido`

Como solamente tenemos dos posibilidades:

- Encendida.
- Apagada.

Podemos resumir eso utilizando un `bool`.

```cpp
bool encendido;
```

Entonces podría ser:

```cpp
true
```

si está encendida, o:

```cpp
false
```

si está apagada.

### `brillo`

También podemos guardar el nivel de brillo de la lucecita.

```cpp
int brillo;
```

Acá necesitamos un número porque el brillo puede ir cambiando.

### `parpadea`

Otra característica podría ser si la luz está parpadeando o no.

```cpp
bool parpadea;
```

Nuevamente tenemos solamente dos posibilidades, así que un `bool` funciona perfecto.


# Muchas lucecitas

También vimos que podemos tener **muchos objetos de la misma clase**.

Por ejemplo:

```cpp
Lucecita luzNavidad[100];
```

Los **corchetes `[]` indican la cantidad**.

Entonces:

```cpp
[100]
```

significa que estamos creando un conjunto de **100 lucecitas**.

Todas pertenecen a la clase `Lucecita`, pero después cada una podría tener distintos valores.

Por ejemplo, una podría estar prendida, otra apagada, otra podría tener más brillo, etc.


# Ejemplo: Espanta Cuco

También apareció el ejemplo de un **Espanta Cuco**.

Podríamos pensar qué cosas necesita tener este objeto.

Por ejemplo:

```cpp
int precio;
Lucecita lucecita;
Sensor sensor;
```

La idea que entendí acá es que **una clase también puede tener dentro objetos que vienen de otras clases**.

Por ejemplo, el Espanta Cuco podría tener:

- Un precio.
- Una lucecita.
- Un sensor.

Entonces empezamos a construir objetos más complejos utilizando otras cosas que ya tenemos creadas.


# LEDs y resistencias

También repasamos una cosa importante de electrónica.

Cuando usamos un **LED**, necesitamos una resistencia para limitar la corriente y no terminar echándonos el LED jejeje.

Normalmente podemos encontrarnos con resistencias como:

- `220 Ω`
- `1 kΩ`

El valor exacto depende del circuito, pero la idea importante es que **el LED no se conecta porque sí directamente a la alimentación**.


# Potenciómetro

El **potenciómetro**, en cambio, generalmente puede funcionar sin agregarle una resistencia externa cuando lo estamos utilizando como divisor de voltaje.

Tiene tres patitas y nos permite obtener distintos valores dependiendo de cuánto movamos la perilla.

Esto después lo podemos leer como una entrada analógica.


# Símbolo de Ground

El símbolo que parece como un triangulito hacia abajo representa **Ground**.

O sea:

**SUELOOOO, TIERRAAAAA.**

`GND` = Ground.

Es la referencia de `0V` dentro del circuito.

# Nombres dentro del código

**NO crear tantas palabras que después sean imposibles de leer.**

Los nombres tienen que explicar lo que hacen, sí, pero tampoco podemos terminar con algo como:

```cpp
cantidadDeVecesQueLaLucecitaFuePresionadaMientrasEstabaEncendida
```

porque después nadie quiere leer eso JAJJA.

La idea es encontrar nombres que sean claros pero manejables.


# `::`

También vimos esta anotación:

```cpp
::
```

Los dos puntos dobles sirven para indicar que algo pertenece a una clase.

Por ejemplo:

```cpp
Perilla::actualizar()
```

Lo puedo leer como:

**`actualizar()` está dentro de la clase `Perilla`.**

O sea:

```cpp
Perilla::
```

significa que lo que viene después pertenece a `Perilla`.

Esto aparece harto cuando tenemos las clases separadas entre el archivo `.h` y el `.cpp`.

Por ejemplo, en el `.h` podríamos declarar:

```cpp
class Perilla {
public:

    void actualizar();

};
```

Y después, en el `.cpp`, explicar qué hace realmente:

```cpp
void Perilla::actualizar() {

}
```

Entonces `::` nos ayuda a decir:

**esta función `actualizar()` es la que pertenece a la clase `Perilla`.**


# GP

`GP` significa **General Purpose**.

Son los pines de propósito general de la placa.

Básicamente son patitas que podemos utilizar para conectar distintas cosas y configurarlas dependiendo de lo que necesitemos hacer.

Por ejemplo:

- Botones.
- LEDs.
- Sensores.
- Otros componentes.


# ADC

`ADC` significa:

**Analog to Digital Conversion**

o sea:

**conversión de analógico a digital**.

Esto sirve porque existen componentes, como un potenciómetro, que nos entregan valores analógicos.

Por ejemplo, una perilla no funciona solamente como:

```text
0 → apagada
1 → encendida
```

Puede estar en muchos puntos intermedios.

El ADC permite que la placa tome esa señal analógica y la transforme en **un número que podamos utilizar dentro del código**.

Entonces podría pasar algo como:

```text
muevo la perilla
        -
cambia el voltaje
        -
ADC lee ese valor
        -
lo transforma en un número
        -
podemos usar ese número en el código
```

Por ejemplo, después podríamos ocuparlo para controlar el brillo de una `Lucecita`.

Mientras más muevo el potenciómetro → cambia el valor que lee el ADC → puedo cambiar el brillo.


Primero creamos una **clase** que funciona como modelo.

Dentro ponemos:

- **Atributos** → información que necesita guardar.
- **Métodos** → cosas que puede hacer.
- **Constructor** → cómo nace o se crea cada objeto de esa clase.

Después podemos crear **muchas instancias** de la misma clase, incluso conjuntos completos como:

```cpp
Lucecita luzNavidad[100];
```

Y además una clase puede empezar a tener dentro objetos de otras clases, como el ejemplo del Espanta Cuco.

Entonces de a poco podemos ir armando cosas mucho más complejas sin tener que escribir absolutamente todo desde cero cada vez.
## encargos

encargo-08a:

1. tomar muchas fotos, mínimo 3 por cada uno de los 3 elementos que estudiamos hoy: perillas, botones, y luces. subir las fotos a su README como respuesta a este encargo, y describirlas textualmente, para con esa info complejizar nuestras clases programadas este viernes.


## Encargo 08a — Perillas, botones y luces

### Perillas

**1. Radio**

![Perilla de radio](./imagenes/p-radio.png)

Esta perilla sirve para buscar las distintas frecuencias de la radio. Al girarla vamos cambiando de estación y podemos moverla hacia ambos lados. Debajo tiene otra perilla más pequeña que permite elegir entre AM, FM y otras bandas.

**2. Microondas**

![Perilla de microondas](./imagenes/p-micro.png)

Esta perilla permite regular el tiempo del microondas. Si la giramos hacia la derecha aumentamos el tiempo y si la giramos hacia la izquierda lo disminuimos. También tiene un botón debajo para seleccionar las funciones.

### Botones

**1. Ascensor**

![Botón de ascensor](./imagenes/b-ascensor.png)

Estos botones sirven para llamar al ascensor e indicar si queremos subir o bajar. Lo interesante es que cuando apretamos uno se ilumina, así sabemos que el ascensor recibió nuestra solicitud y no tenemos que seguir apretándolo.

**2. Gimnasio**

![Botón para llamar al profesor](./imagenes/b-gym.png)

Este botón sirve para llamar a un profesor cuando tenemos alguna duda. Lo diferente es que hay que mantenerlo presionado durante 2 segundos para que funcione, no basta con apretarlo una vez rápidamente.

**3. Micro**

![Botón de micro](./imagenes/b-micro.png)

Este botón sirve para avisarle al conductor que queremos bajar. Solo tenemos que apretarlo una vez y se activa la señal de parada, no es necesario mantenerlo presionado.

### Luces

**1. Mouse**

![Luz del mouse](./imagenes/l-mouse.png)

Esta luz está debajo del mouse y es parte del sensor que detecta el movimiento. A diferencia de otras luces, no está para iluminar o avisarnos de algo, sino para ayudar a que el mouse funcione.

2. partir del ejemplo de hoy, que está subido en codigos/ de hoy, y hacer que las luces parpadeen. para eso, definir parpadeo de forma paramétrica.

## lectura

En estas páginas entendí más que nada que cuando una herramienta tiene conocimiento metido dentro, igual uno termina dependiendo de ella para poder usar ese conocimiento. Me gustó que el texto lo conectara con los softwares actuales, porque al final pasa mucho eso de ocupar algo sin entender completamente qué está haciendo por detrás. También habla de los modelos físicos y de cómo servían para volver visibles cosas súper abstractas, sobre todo en matemáticas. Siento que acá la idea ya no es solo que las herramientas ayudan a hacer cosas, sino que también terminan cambiando la forma en que entendemos y usamos el conocimiento.

“Instrumental knowledge is a vital but fragile disciplinary capacity that can be lost.”- pág.56

“mathematical principles are very often hidden behind their effects on the screen.”- pág.57
