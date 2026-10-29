# sesion-10b

## apuntes sesión

no fui :( 

## encargos

### avance proyecto-2 

asignamos tareas para el lunes 

1.  Diagramas de flujo sobre: (Cami)
•  Uso usuario general
•  Diseño general 
2.  Carcasa (Bianka)
3.  Pseudo Código general + escenarios que no queremos (Daya + Cami)
4.  Esquematico (Daya + Cami)
5.  Describir lo que vamos a presentar (Daya)
6.  Nombre proyecto
7.  class Led (Bianka)
8.  Pulir concepto README (Bianka)

### clase Lucecita

siguiendo el ejemplo visto en clase https://wokwi.com/projects/477335809803977729, lo que necesitamos es crear una clase general Lucecita para controlar las cinco luces LED, permitiendo encenderlas y apagarlas mediante funciones reutilizables.

en el archivo Lucecita.h se declarara la clase general Lucecita, definiendo las variables necesarias para identificar el pin al que está conectada cada luz y conocer su estado, además de declarar los métodos para encenderla y apagarla.

en el archivo Lucecita.cpp se desarrollara el funcionamiento de estos métodos. Se configurara el pin como salida mediante el constructor y se definieron las instrucciones para activar (prender)  o desactivar (apagar) la luz. 

Finalmente, en el archivo main.cpp se realizara una prueba creando distintas instancias de la clase Lucecita, asignando un pin diferente a cada LED. A través de un ciclo, se espera que cada luz pudiera encenderse y apagarse de manera secuencial para reutilizarse y poder controlar varios LED. 

Método constructor Lucecita():
- Recibir el número del pin.
- Configurar el pin como salida.
- Inicializar la luz apagada.

Método prender():
- Cambiar el estado de la luz a encendida.
- Activar el pin para encender la luz.

Método apagar():
- Cambiar el estado de la luz a apagada.
- Desactivar el pin para apagar la luz.


### Lucecita.h 

```cpp
#ifndef LUCECITA_H
#define LUCECITA_H

#include "hardware/gpio.h"

// CLASE Lucecita
//   Guardar el número del pin GPIO.
//   Guardar si la luz está encendida o apagada.
//   Permitir encender y apagar la luz.

class Lucecita {
  public:

    // Atributos
    int patita;
    bool prendida = false;

    // Constructor:
    // Recibe el pin donde está conectada la luz.
    Lucecita(int nuevaPatita);

    // Métodos para controlar la luz.
    void prender();
    void apagar();
    
};

#endif
```
### Lucecita.cpp

```cpp
#include "Lucecita.h"

// Recibir el número del pin.
// Guardar el número.
// Inicializar el GPIO.
// Configurar el pin como salida.
// Dejar la luz apagada inicialmente.

Lucecita::Lucecita(int nuevaPatita) {
    patita = nuevaPatita;

    gpio_init(patita);
    gpio_set_dir(patita, GPIO_OUT);

    apagar();
}

// metodo prender():
//   Cambiar el estado a encendido.
//   Activar el pin GPIO.

void Lucecita::prender() {
    prendida = true;
    gpio_put(patita, true);
}

// metodo apagar():
//   Cambiar el estado a apagado.
//   Desactivar el pin GPIO.

void Lucecita::apagar() {
    prendida = false;
    gpio_put(patita, false);
}

// Metodo parpadeo (): 
// se prende luz pasa tiempo
// de determinado tiempo se apaga 
// se repite la accion
// no ocupar el  sleep_ms
void Luccecita::parpadeo() {

}
```
### Main.cpp

```cpp
#include "pico/stdlib.h"
#include "Lucecita.h"


// Crear cinco objetos Lucecita.
// Asignar un pin GPIO diferente a cada luz.

Lucecita luz1(2);
Lucecita luz2(3);
Lucecita luz3(4);
Lucecita luz4(5);
Lucecita luz5(6);

int main() {


    // Iniciar el sistema.
    // Repetir continuamente la secuencia de luces.

    while (true) {

        // Encender luz 1, esperar y apagar.
        luz1.prender();
        sleep_ms(500);
        luz1.apagar();

        // Encender luz 2, esperar y apagar.
        luz2.prender();
        sleep_ms(500);
        luz2.apagar();

        // Encender luz 3, esperar y apagar.
        luz3.prender();
        sleep_ms(500);
        luz3.apagar();

        // Encender luz 4, esperar y apagar.
        luz4.prender();
        sleep_ms(500);
        luz4.apagar();

        // Encender luz 5, esperar y apagar.
        luz5.prender();
        sleep_ms(500);
        luz5.apagar();

   
        // Al terminar con la quinta luz,
        // volver a comenzar desde la primera.
    }

    return 0;
}
```
### mejorar 

idealmente, no ocupar sleep_ms(500) por que va a estar bloqueando medio segundo por ende en ese perido no va a ponder sonar algo :( 

### según chat gpt 

"Exacto. En tu proyecto conviene evitar sleep_ms(500) porque pausa la ejecución del programa durante 500 milisegundos. Mientras está esperando, el código deja de consultar el encoder y atender otras tareas, lo que podría interferir con la reproducción del sonido.

La solución es utilizar un control de tiempo sin bloqueo, mediante time_us_32(), para comprobar si ya transcurrió el intervalo de parpadeo sin detener el programa" 


## lectura

