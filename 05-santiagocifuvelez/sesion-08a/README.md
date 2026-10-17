# sesion-08a
Hola Emi, profe Aarón, Misa y Sebas.  

Luego de 2 meses intensos, logré culminar la primera etapa de mi anteproyecto de grado, junto con la compañía y el apoyo del profesor Aarón (en Chile oficial) y Gustavo (en Colombia oficial).
Gracias a ustedes por la flexibilidad y la compresión para con el proyecto. Ahora es momento de ponerme al día con el taller, motivo por el cual extendí mi estadía en el país.

Estuve revisando los repositorios de mis compañerxs junto al calendario del curso para guiarme en que etapa del semestre estamos (comparando temas con fechas), para poder ponerme al día. Y encontré que estamos viendo programación en C++ para chips RP2040. Así que comencemos.

>[!NOTE]
>
>Para poder organizarme, clasifique los temas que se están viendo, en este orden para poder repasarlos y estudiarles:
>
> ## Programación orientada a objetos (POO)
> 1. Estructuras macro para los textos:
>
>`Archivos .h`
>`Archivos .cpp`
>
> 2. Tangibles:
>     
>`Botones`
>`Perillas`
>`Luces` 

# Apuntes sesión

## Programación orientada a objetos (POO)
Es una forma de programar donde, en vez de escribir instrucciones sueltas, creas “cosas” (objetos) que tienen sus propias características y acciones. Sirve para ordenar el código y evitar repetir instrucciones. Es como armar un programa con piezas de Lego.

**Conceptos básicos:**

`Clase (class):` el molde o plano. Define cómo será algo (por ejemplo, “cómo es un auto”).  
`Objeto:` una cosa concreta hecha con ese molde (mi auto rojo).  
`Atributos:` variables dentro de la clase; lo que el objeto tiene (color, velocidad).  
`Métodos:` funciones dentro de la clase; lo que el objeto hace (acelerar, frenar).  
`Constructor:` método con el mismo nombre de la clase; se ejecuta al crear el objeto y le da sus valores iniciales.  
`public / private:` en C++ defines qué partes se pueden usar desde afuera (public) y cuáles quedan protegidas dentro de la clase (private).  
`Herencia:` una clase puede tomar lo de otra y agregarle cosas nuevas (class Camioneta : public auto).  

**En resumen:**
Se hace el molde una sola vez y creas todos los objetos que quieras, sin repetir código.

**Ejemplo:**
Una receta de galletas (la clase) y las galletas que salen (los objetos). Todas siguen la misma receta, pero cada una puede tener distinto sabor.


## Clase vs. objeto
*aquí use un ejemplo de galletas while working con claude para poder entender. Una metáfora*
*también estoy estudiando con este ejemplo creado en clase con el profesor Aarón, periodo: [ejemplo en wokwi](https://wokwi.com/projects/477335809803977729)* 

- **Clase**: el *molde de galletas* (o la receta). Define qué forma tiene y qué puede hacer. Todavía no es una galleta.
- **Objeto**: una *galleta* hecha con ese molde. Cada galleta puede tener su propio sabor.

En el código:

```cpp
Boton pulsador(7);     // un objeto "pulsador" hecho con el molde Boton, conectado al pin 7

Lucecita luz(6);       // un LED en el pin 6
Lucecita luzDos(5);    // otro LED en el pin 5
```

Con **un solo molde** (`Lucecita`) hacemos **dos objetos** (`luz` y `luzDos`).


## ¿Por qué dos archivos por clase (`.h` y `.cpp`)? 
Se puede escribir todo en un solo archivo, pero con muchos componentes se vuelve larguísimo y difícil de ordenar.

La regla es simple: **cada cosa tiene su propio espacio**. Así `main.cpp` queda corto y solo dice **qué hacer**, no **cómo se hace**.

| Archivo | Qué contiene | Analogía |
|---|---|---|
| `.h` (header / encabezado) | **Qué tiene y qué puede hacer** la clase (la lista) | La portada de una receta: nombre e ingredientes |
| `.cpp` | **Cómo se hace** cada acción (el código real) | Los pasos de la receta |
| `main.cpp` | **Usa** las clases | El cliente que pide la comida |

Ejemplo: `Lucecita.h` solo dice "un LED tiene `prender()`, `apagar()` y `parpadear()`". Las instrucciones reales para prenderlo están en `Lucecita.cpp`.

Y `main.cpp` escribe `#include "Lucecita.h"` para decir: "voy a usar LEDs, muéstrame qué pueden hacer".


Estructura del proyecto

Todos los archivos van en la misma carpeta, sin subcarpetas:

```
proyecto/
├── main.cpp
├── Boton.h
├── Boton.cpp
├── Perilla.h
├── Perilla.cpp
├── Lucecita.h
├── Lucecita.cpp
└── diagram.json
```

`diagram.json` es el archivo que le dice a Wokwi cómo está armado el circuito (Pico, LEDs, botón, perilla y cables). Sin él, el código no tiene nada que controlar.

### Orden para escribir el código

Para cada clase, siempre el mismo orden:

1. Escribir el `.h` primero (decidir qué tiene la clase)
2. Escribir el `.cpp` después (programar cómo funciona)
3. Repetir para cada clase
4. Al final, escribir `main.cpp` (usar todo)

---

## Esqueleto de un archivo `.h`

Cada `.h` empieza y termina así (se llama *include guard*):

```cpp
#ifndef LUCECITA_H
#define LUCECITA_H

// aquí va la declaración de la clase

#endif
```

Cambia el nombre según el archivo: `BOTON_H` en `Boton.h`, `PERILLA_H` en `Perilla.h`.

> La explicación de para qué sirve el include guard viene en el paso 2.


# encargos

encargo-08a:

1. tomar muchas fotos, mínimo 3 por cada uno de los 3 elementos que estudiamos hoy: perillas, botones, y luces. subir las fotos a su README como respuesta a este encargo, y describirlas textualmente, para con esa info complejizar nuestras clases programadas este viernes.

2. partir del ejemplo de hoy, que está subido en codigos/ de hoy, y hacer que las luces parpadeen. para eso, definir parpadeo de forma paramétrica.

## lectura
