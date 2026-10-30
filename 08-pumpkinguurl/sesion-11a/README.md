# sesion-11a

## apuntes sesión

Seguimos con el trabajo en clases. Pasamos el pseudo código por IA para que nos ayudara a formalizarlo en un código real 

```cpp
//promesas de lo que queremos que el botón haga
#ifndef BOTON_H
#define BOTON_H

#include "pico/stdlib.h"
//hay que incluir lo del gpio
#include "hardware/gpio.h"


//uno de los botones servirá como botón
//encendido o apagado / mantener apretado
//y seleccionador / un toque

//el otro botón servirá para mantener al personaje volando

class Boton
{
  public: 

    // atributos
    bool presionado = true;
    // tiempo presionado
    int tiempoPresionado;
    bool encendido;
    int patita; 
    
    // constructor
    //Boton(int nuevaPatita);
    //no se donde va definido en este caso

    //metodos
    void 
    //siempre se ponia void?
    //pa cualquiera?

    //metodos

    // botón1: dos variables
    // if boton presionado >= 2sg
    // la pantalla se inicia
    // si se vuelve a apretar por 2sg
    // la pantalla se apaga

    // la segunda opción de este botón
    // if boton presionado <= 2sg
    // recorrer personajes con perilla2
    // presionar botón <= 2sg

    // botón2: una variable
    // si presionado = true
    // el personaje baja
    // si presionado = false
    // el personaje sube
};

#endif

```

Y nos entregó esto

```cpp
#ifndef BOTON_H
#define BOTON_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Clase genérica para un botón físico en la Pico.
// Sirve para los dos botones del juego: ella solo "informa" qué pasó
// (toque, mantenido, presionado); el juego decide qué hacer con eso.
//
// Conexión: un lado del botón al GPIO y el otro a GND (usa pull-up interno).
class Boton
{
  public:
    // constructor: recibe el número de GPIO (la "patita") y,
    // opcionalmente, cuánto hay que mantener para que cuente como "largo"
    Boton(uint patita, uint32_t umbralLargoMs = 2000);

    // configura el pin; se llama UNA vez en el setup
    void iniciar();

    // lee el botón y actualiza todo; se llama en CADA vuelta del loop
    void actualizar();

    // ---- para el botón 2 (mantener = personaje vuela) ----
    // true mientras el botón esté apretado
    bool estaPresionado() const;

    // ---- para el botón 1 (encender/apagar y seleccionar) ----
    // true UNA sola vez cuando se suelta tras un toque corto (< umbral)
    bool huboToque();
    // true UNA sola vez cuando se completa el tiempo de mantenido (>= umbral)
    bool huboMantenido();

    // cuánto lleva apretado (ms); 0 si no está apretado
    uint32_t tiempoPresionado() const;

  private:
    uint patita;
    uint32_t umbralLargoMs;

    bool presionado;          // estado estable (ya filtrado)
    bool ultimaLectura;       // última lectura cruda del pin
    uint32_t ultimoCambioMs;  // cuándo cambió la lectura cruda
    uint32_t inicioPresionMs; // cuándo empezó la presión estable

    bool toqueListo;          // evento pendiente: toque corto
    bool mantenidoListo;      // evento pendiente: mantenido largo
    bool mantenidoEmitido;    // para no repetir el mantenido mientras sigue apretado

    static const uint32_t REBOTE_MS = 20; // filtro anti-rebote
};

#endif
```

Antes de comenzar con esta parte más personal del proceso de creación del código le pedimos a la IA que nos hiciera un una de cómo se vería más o menos el juego que queríamos crear. Nos entregó un montón de archivos con todo separado: animaciones, juego, botón, perillas, conexiones. Entiendo la lógica detrás de tener muchos archivos, pero ¿era realmente necesario?, se lo pregunte y me dijo que no, pero para no tener un main con +1000 líneas era mejor tener todo separado y así, en caso de tener algún error es más fácil arreglarlo. Le creo.

He aprendido la importancia de definir bien lo que queremos hacer, que sea coherente y detallado pero conciso, para que los demás o la IA pueda entender bien de qué trata el proyecto


## encargos

## lectura
