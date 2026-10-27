# sesion-09b
viernes 16 de octubre

## apuntes sesión
no fuimos todo el grupo a clases y no nos organizamos, así que aquí ira autoestudio para seguir entendiendo las clases

le pedí a claude que me fuera guiando paso a paso para entender:

### clase y objeto

- **clase:** es el molde. describe cómo es algo y qué sabe hacer. ejemplo: `Lucecita`.
- **objeto:** es el objeto hecho con ese molde. ejemplo: luz de mi pieza y luz de mi living.

cada objeto tiene sus propios valores, aunque salgan del mismo molde (`Lucecita`)

```cpp
Lucecita luzPieza;     // objeto 1
Lucecita luzLiving;    // objeto 2
```
a la izquierda va la clase y a la derecha el objeto.

la clase define qué atributos y métodos existen: toda `Mascota` tiene por ejemplo nombre, edad y sabe ladrar.

cada objeto tiene sus valores concretos.

___

tengo la duda de cómo saber diferenciar los atributos y métodos de una clase y como ver los que son particulares a un solo objeto dentro de la clase, a nivel de sintaxis general del código completo.

me hizo este código de ejemplo:

```cpp
#include <iostream>
#include <string>
using namespace std;

// ============ LA CLASE (el molde) ============
class Mascota {
public:
    // ATRIBUTOS: lo que tiene cada mascota
    string nombre;
    int edad;

    // MÉTODOS: lo que sabe hacer cada mascota
    void presentarse() {
        cout << "Hola, soy " << nombre << " y tengo " << edad << " años." << endl;
    }

    void cumplirAnios() {
        edad = edad + 1;
    }
};   // <- el ; final es obligatorio

// ============ EL PROGRAMA ============
int main() {
    // Creo dos OBJETOS con el molde Mascota
    Mascota pelusa;
    pelusa.nombre = "Pelusa";
    pelusa.edad = 3;

    Mascota rocky;
    rocky.nombre = "Rocky";
    rocky.edad = 7;

    // Uso los métodos
    pelusa.presentarse();
    rocky.presentarse();

    rocky.cumplirAnios();      // solo Rocky cumple años

    pelusa.presentarse();
    rocky.presentarse();

    return 0;
}
```

**mapa general:**

```cpp
CLASE Mascota (molde, se escribe una vez)
├── atributos: nombre, edad
└── métodos:   presentarse(), cumplirAnios()

OBJETO pelusa            OBJETO rocky
├── nombre = "Pelusa"    ├── nombre = "Rocky"
└── edad   = 3           └── edad   = 7 → 8 (tras cumplirAnios)
```

**cómo se ordenan los archivos**

```cpp
Mascota.h     ← la promesa (qué tiene y qué hace la clase)
Mascota.cpp   ← el cómo (código de los métodos)
main.cpp      ← el programa que crea y usa objetos
```
respecto a los `#include`:

- Mascota.cpp incluye Mascota.h, porque necesita conocer la clase para escribir sus métodos.
- main.cpp incluye Mascota.h, porque necesita conocer la clase para crear objetos.
- Nadie incluye un .cpp. Solo se incluyen .h.

**sintaxis:**

- atributo = tipo + nombre + `;`
- método = tipo + nombre + `()` + `;`
- todo dentro de `{}`
- la clase cierra con `};` (llave y punto y coma).

```cpp
class Mascota {
public:
    string nombre;
    int edad;

    void ladrar();
};
```

### tipos de atributos

| tipo | guarda | ejemplo |
| --- | --- | --- |
| `int` | número entero | `int edad;` |
| `float` / `double` | número con decimales | `float peso;` |
| `bool` | verdadero o falso | `bool encendida;` |
| `char` | una letra | `char inicial;` |
| *otra clase* | un objeto completo | `Lucecita espantadora;` |

### tipos de métodos
esto es realmente el tipo de retorno, y dice qué devuelve el método al terminar. 

```cpp
void ladrar();        // void = no devuelve nada, solo hace algo
int obtenerEdad();    // devuelve un número entero
bool tieneHambre();   // devuelve verdadero o falso
```
un método puede recibir datos entre parentesis, que se llaman parámetros*

```cpp
void cumplirAnios(int cuantos);
```


## encargos

## lectura
