# sesion-08a

## apuntes sesión

## encargos

encargo-08a:

1. tomar muchas fotos, mínimo 3 por cada uno de los 3 elementos que estudiamos hoy: perillas, botones, y luces. subir las fotos a su README como respuesta a este encargo, y describirlas textualmente, para con esa info complejizar nuestras clases programadas este viernes.

2. partir del ejemplo de hoy, que está subido en codigos/ de hoy, y hacer que las luces parpadeen. para eso, definir parpadeo de forma paramétrica.

https://wokwi.com/projects/477403274082177025

### Paso 01: agregar el método parpadear()

Partí del código de clases, donde ya teníamos `Lucecita.h` y `Lucecita.cpp`, con los métodos `prender()` y `apagar()`.

La idea era agregar un método para que la luz parpadeara, pero que pudiéramos cambiar sus tiempos sin tener que modificar todo el código.

En `Lucecita.h` agregué:

```cpp
void parpadear(int tiempoEncendida, int tiempoApagada);
```
- `int tiempoEncendida`: tiempo que el LED permanece prendido.
- `int tiempoApagada`: tiempo que permanece apagado.

### Paso 02: resolver primer problema: sleep_ms()

Al principio hice el parpadeo usando `sleep_ms()`, para esperar entre prender y apagar la luz, pero apareció un error porque `sleep_ms()` no era reconocido en `Lucecita.cpp`. Para solucionarlo tuve que incluir `pico/stdlib.h`, que ya estábamos usando en `main.cpp`.

Después conseguí que la luz parpadeara, pero apareció otro problema: **al presionar el botón por segunda vez, la luz no se apagaba inmediatamente**.

Esto pasaba porque `sleep_ms()` hace que el programa espere antes de continuar. Durante esa espera no podía leer si el botón estaba siendo presionado.

chatgpt me pasó estos códigos para controlar el tiempo:

- `get_absolute_time()`: obtiene el tiempo actual.
- `to_ms_since_boot()`: permite trabajar con ese tiempo en milisegundos.
- `ultimoCambio`: atributo que guarda cuándo cambió por última vez el estado de la luz.

Así, en vez de detener el programa esperando, el método revisa si ya pasó el tiempo necesario para cambiar la luz de prendida a apagada, o al revés.

### paso 03: hacer que el botón prenda y apague el parpadeo

Después trabajé en `main.cpp` para que el botón funcionara como un interruptor:

- Primera pulsación: comienza el parpadeo.
- Segunda pulsación: se detiene y la luz queda apagada.

Para eso agregué estas variables:

```cpp
bool sistemaPrendido = false;
bool botonEstadoAnterior = false;
```

**¿Por qué necesitaba las dos?**

`sistemaPrendido` guarda si el parpadeo está activado o no.

`botonEstadoAnterior` guarda cómo estaba el botón en la lectura anterior.


### Paso 04: agregar una segunda luz

Después agregué otro LED al circuito, conectado al pin GP5. El primero estaba conectado al GP6, copié la formula anterior del primer led.

Para el segundo LED utilicé la perilla.

Quería que la luz parpadeara a una velocidad fija solamente cuando la perilla estuviera en cierta posición, y que se apagara cuando saliera de ese rango.

```cpp
if (parpadeo.posicion >= 2000 && parpadeo.posicion <= 3000) {
  luzSegunda.parpadear(250, 250);
} else {
  luzSegunda.apagar();
}
```

La perilla entrega valores entre 0 y 4095.

- `>= 2000`: la posición tiene que ser mayor o igual a 2000.
- `<= 3000`: también tiene que ser menor o igual a 3000.
- `&&`: las dos condiciones tienen que cumplirse.

Cuando está entre esos valores, la segunda luz parpadea con 250 ms prendida y 250 ms apagada, lo que equivale a 2 Hz.

Si sale de ese rango, se apaga.

### Resultado final

Terminé con dos luces que funcionan de manera independiente:

- **LED 1 (GP6):** parpadea con tiempos de 500 ms y se prende o apaga usando el botón.
- **LED 2 (GP5):** parpadea con tiempos de 250 ms cuando la perilla está entre 2000 y 3000. Fuera de ese rango se apaga.



## lectura
