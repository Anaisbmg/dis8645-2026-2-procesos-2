# prueba-plexor

Programa de ejemplo para leer **3 potenciómetros** con una **Raspberry Pi Pico 2** usando un multiplexor analógico. El programa muestra en el monitor serial un valor de **0 a 99** para cada potenciómetro.

Está pensado para estudiantes que recién empiezan con el código: cada línea de [main-0-99.cpp](main-0-99.cpp) tiene un comentario que explica qué hace.

## El multiplexor: plexo

Usamos la placa **plexo** de [piruetasxyz/plexo](https://github.com/piruetasxyz/plexo/tree/main), un multiplexor de 6 potenciómetros para Raspberry Pi Pico. La placa usa un chip **74HC4051**, que tiene 8 canales. Los canales 6 y 7 están conectados a tierra, así que quedan 6 libres para potenciómetros.

En ese repositorio están el esquemático y el diseño de la placa en KiCad (carpeta `plexo-v-0-rev-a/`).

### ¿Para qué sirve un multiplexor?

La Pico tiene solo 3 entradas analógicas (ADC). Un multiplexor funciona como un **interruptor selector**: tiene varias entradas y una sola salida, y con 3 pines digitales (S0, S1 y S2) elegimos cuál entrada pasa a la salida. Así podemos leer hasta 6 potenciómetros usando **una sola** entrada analógica de la Pico.

Con los 3 pines formamos un número en binario, que es el canal elegido:

| Canal | S2 | S1 | S0 |
|:-----:|:--:|:--:|:--:|
| 0     | 0  | 0  | 0  |
| 1     | 0  | 0  | 1  |
| 2     | 0  | 1  | 0  |
| 3     | 0  | 1  | 1  |
| 4     | 1  | 0  | 0  |
| 5     | 1  | 0  | 1  |

El programa va cambiando de canal muy rápido (0, 1, 2, 0, 1, 2…) y lee cada potenciómetro por turnos.

## Conexiones

El conector J3 de plexo va a la Pico así:

| plexo (J3) | Pico 2              | Pin físico |
|------------|---------------------|:----------:|
| 3V3        | 3V3(OUT)            | 36         |
| salida     | GP26 (ADC0)         | 31         |
| GND        | AGND                | 33         |
| S0         | GP2                 | 4          |
| S1         | GP3                 | 5          |
| S2         | GP4                 | 6          |

Los 3 potenciómetros van en los canales **0, 1 y 2** de plexo.

Dos cosas importantes, según la documentación de plexo:
- Conecta la tierra a **AGND** (tierra analógica) y no a otro GND, porque así las lecturas tienen menos ruido.
- **No** alimentes los potenciómetros desde ADC_VREF. Ese pin tiene una resistencia interna que baja el voltaje cuando los potenciómetros consumen corriente, y las lecturas quedan mal.

## Cómo usarlo

1. Abre esta carpeta en VS Code con la extensión **Raspberry Pi Pico** instalada.
2. Revisa que [CMakeLists.txt](CMakeLists.txt) compile el archivo correcto:
   ```cmake
   add_executable(prueba-plexor main-0-99.cpp)
   ```
3. Conecta la Pico manteniendo apretado el botón **BOOTSEL** y presiona **Run** en la extensión (o compila y copia el archivo `.uf2` de la carpeta `build/` a la Pico).
4. Abre el **monitor serial** (Serial Monitor en VS Code) y elige el puerto de la Pico.
5. Mueve los potenciómetros. Deberías ver algo así:
   ```
   pote0: 42   pote1:  7   pote2: 99
   pote0: 43   pote1:  7   pote2: 99
   ```

## Cómo funciona

El programa tiene tres partes:

1. **`configurar()`**: se ejecuta una vez al comienzo. Activa la comunicación USB, configura los pines S0, S1 y S2 como salidas y prepara el ADC en el pin GP26.
2. **`leerPote(numero)`**: elige el canal del multiplexor, lee el voltaje, le quita el ruido y lo convierte a un número de 0 a 99.
3. **`main()`**: repite para siempre: lee los 3 potenciómetros, imprime los valores y espera 50 milisegundos.

### Lectura de un canal

Al cambiar de canal, el multiplexor necesita un momento para estabilizarse. Por eso el programa:
1. cambia los pines S0, S1 y S2,
2. espera 10 microsegundos,
3. hace una primera lectura y la descarta (puede salir mal),
4. recién ahí guarda las lecturas buenas.

### El ruido y cómo lo quitamos

Aunque no toques un potenciómetro, su lectura "tiembla" unas 10 unidades. Eso es normal en el ADC de la Pico y se llama **ruido**. El programa usa tres trucos para eliminarlo:

| Truco | Constante | Qué hace |
|-------|-----------|----------|
| Promedio | `LECTURAS_POR_PROMEDIO` | Lee 16 veces seguidas y saca el promedio. |
| Suavizado | `SUAVIZADO` | Mezcla cada lectura nueva con las anteriores, para que los saltos se noten menos. |
| Zona muerta | `ZONA_MUERTA` | Solo acepta un cambio si el valor se movió al menos 6 unidades. |

Además, el programa pone el pin **GP23** en alto. En la Pico 2, eso hace que la fuente de energía interna trabaje en un modo con menos ruido.

### De 0–4095 a 0–99

El ADC de la Pico entrega números de **0 a 4095** (12 bits). Para pasarlos a 0–99 hacemos una regla de tres:

```
valor = lectura * 100 / 4096
```

Por ejemplo, con el potenciómetro a la mitad: `2048 * 100 / 4096 = 50`.

> En el repositorio de plexo los ejemplos hablan de valores de 0 a 65535. Esa es otra escala (16 bits) que usan algunos lenguajes, como MicroPython. Aquí, en C++ con el Pico SDK, la escala es de 0 a 4095.

## Ajustes

Todos los números que puedes cambiar están al comienzo de [main-0-99.cpp](main-0-99.cpp):

- **Si el valor sigue temblando** con el potenciómetro quieto: sube `ZONA_MUERTA` (por ejemplo a 10) o `SUAVIZADO` a 3.
- **Si el valor responde lento**: baja `SUAVIZADO` a 1.
- **Otra escala**: cambia `VALOR_MAXIMO` (por ejemplo a 127 para MIDI).
- **Más potenciómetros**: plexo admite hasta 6. Sube `CANTIDAD_POTES` y agrega las lecturas en `main()`.
- **Si un potenciómetro va al revés** (baja cuando lo giras a la derecha): tiene los pines invertidos. Puedes arreglarlo en el código con `VALOR_MAXIMO - valor`.
- **Si usas una Pico 2 W**: borra las 3 líneas del pin 23 en `configurar()`, porque en esa placa ese pin no funciona igual.

## Archivos

| Archivo | Qué es |
|---------|--------|
| [main-0-99.cpp](main-0-99.cpp) | Versión de ejemplo comentada (0 a 99). |
| [main.cpp](main.cpp) | Versión anterior, más compacta, con valores de 0 a 4095. |
| [CMakeLists.txt](CMakeLists.txt) | Le dice al compilador qué archivo compilar y qué librerías usar. |
| `pico_sdk_import.cmake` | Archivo del Pico SDK, no hay que modificarlo. |
