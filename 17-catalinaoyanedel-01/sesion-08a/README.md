# sesion-08a
martes 06 de octubre

## apuntes sesión
### repaso clases
- las clases tienen atributos y métodos
- OOP: significa Object-Oriented Programming, un modelo o paradigma de desarrollo de software que organiza el diseño de programas alrededor de datos u objetos en lugar de funciones y lógica secuencial.

### ejemplo clase Lucecita
- la luz tiene un estado que se llama encendido (sí o no)
- puede existir un parámetro que determine que tan encendido está (brillo), ejemplo: 0-255
- estos parámetros se definen según el umbral
- tiene parpadeo, el cual depende del tiempo
- `LuzNavidad = Lucecita [100];`
- color = rojo, verde, azul

```cpp
class EspantaCuco
  int precio;
Lucecita espantadora;
Sensor luminico;
```

**tipo de archivo**
- `.h`: palabras, saber qué hace
- `.cpp`: saber cómo lo hace
  
un .h es como un hombre que solo promete y un .cpp es un hombre que sabe cómo hacer lo que promete

### profundización contenidos
me ha costado entender la materia que estamos pasando, principalmente más desde el cómo hacerlo y poder replicarlo yo. estuve resfriada y tuve unos problemas personales que me han hecho atrasarme, pero quiero ir entendiendo mejor la materia con este repaso para prepararme mejor para el proyecto 01

tengo entendido:
- para qué sirven las clases de manera general 
- qué son los métodos
- qué son los atributos

me cuesta:
- los constructores
- el orden del código
- sintaxis

le di el siguiente prompt a claude:
> "quiero profundizar en mis apuntes de este día, estamos aprendiendo programación orientada a objetos, viendo Clases en C++, a continuación te entrego mis apuntes, dame definiciones, explicaciones y ejemplos para entender con mayor profundidad."

___________________

### repaso de lo que ya entiendo

- **clase:** un molde o plano que describe cómo es y qué hace un tipo de cosa. no es la cosa en sí.
- **objeto:** una cosa concreta creada a partir de ese molde. la clase `Lucecita` es el plano; `luz1` y `luz2` son lucecitas reales.
- **atributos:** los datos que guarda cada objeto (variables dentro de la clase). para Lucecita: `encendida`, `brillo`, `color`.
- **métodos:** las acciones que el objeto puede hacer (funciones dentro de la clase). para Lucecita: `encender()`, `apagar()`, `parpadear()`.

### ejemplo de clase

```cpp
class Lucecita {
private:
    bool encendida;      // atributo: ¿está prendida?
    int brillo;          // atributo: 0 a 255
    int pin;             // atributo: pin de la Pico donde está conectada

public:
    Lucecita(int numeroPin);   // constructor
    void encender();           // método
    void apagar();             // método
    void setBrillo(int valor); // método
    bool estaEncendida();      // método
};
```

**cosas importantes:**
- `private`: solo la propia clase puede tocar esos atributos. así nadie desde afuera pone brillo = 9999 por error.
- `public`: lo que el resto del programa sí puede usar.
- el punto y coma `;` después de la llave de cierre `}` es obligatorio en las clases. es el error de sintaxis más común.

en nuestro caso solo usaremos public

### constructores
método especial que se ejecuta automáticamente en el momento en que creas un objeto. sirve para dejarlo en un estado inicial válido. sin constructor, los atributos quedan con basura (valores al azar). si `encendida` no se inicializa, tu luz podría partir prendida sin que tú lo hayas decidido.

**cómo reconocerlo**
- se llama igual que la clase.
- no tiene tipo de retorno (ni `void`, ni `int`, nada).

```cpp
Lucecita(int numeroPin);   // ✅ constructor
void Lucecita(int n);      // ❌ error: tiene "void"
```

**implementación (en el .cpp):**
```cpp
Lucecita::Lucecita(int numeroPin) {
    pin = numeroPin;
    encendida = false;
    brillo = 0;
}
```


## encargos

encargo-08a:

1. tomar muchas fotos, mínimo 3 por cada uno de los 3 elementos que estudiamos hoy: perillas, botones, y luces. subir las fotos a su README como respuesta a este encargo, y describirlas textualmente, para con esa info complejizar nuestras clases programadas este viernes.

2. partir del ejemplo de hoy, que está subido en codigos/ de hoy, y hacer que las luces parpadeen. para eso, definir parpadeo de forma paramétrica.

## lectura

