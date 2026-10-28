// main-0-99.cpp
// versión de ejemplo para aprender:
// lee 3 potenciómetros a través de un multiplexor (74HC4051 / CD4051)
// y muestra en el monitor serial un valor de 0 a 99 para cada uno.
//
// placa: raspberry pi pico 2, pico sdk, c++

// ---------------------------------------------------------------------------
// 1. librerías
// ---------------------------------------------------------------------------
// una librería es código que alguien ya escribió y que podemos usar.

#include <cstdio>             // para printf(), que escribe texto en el monitor serial
#include <cstdlib>            // para abs(), que calcula el valor absoluto de un número
#include "pico/stdlib.h"      // funciones básicas del pico: pines, pausas, usb, etc.
#include "hardware/adc.h"     // funciones del adc (el conversor que lee voltajes)

// ---------------------------------------------------------------------------
// 2. configuración
// ---------------------------------------------------------------------------
// "const" significa que el valor es constante: nunca cambia mientras el
// programa funciona. ponemos todos estos números aquí arriba para poder
// cambiarlos fácilmente sin buscar por todo el código.

// pines que eligen el canal del multiplexor.
// el multiplexor tiene 8 canales (0 a 7) y se elige uno con 3 pines,
// cada uno puede estar apagado (0) o encendido (1), igual que un número binario:
//   canal 0 = S2:0 S1:0 S0:0
//   canal 1 = S2:0 S1:0 S0:1
//   canal 2 = S2:0 S1:1 S0:0
const uint PIN_S0 = 2;
const uint PIN_S1 = 3;
const uint PIN_S2 = 4;

// pin donde llega la señal del multiplexor (la salida "común" o "Z").
// el gpio 26 del pico es la entrada analógica ADC0.
const uint PIN_MUX_SALIDA = 26;
const uint ENTRADA_ADC = 0;

// cuántos potenciómetros tenemos (conectados a los canales 0, 1 y 2)
const uint CANTIDAD_POTES = 3;

// el valor más alto que queremos mostrar (los valores irán de 0 a 99)
const int VALOR_MAXIMO = 99;

// el adc del pico entrega números de 0 a 4095 (12 bits).
const int ADC_MAXIMO = 4095;

// ---------------------------------------------------------------------------
// 3. configuración del filtro de ruido
// ---------------------------------------------------------------------------
// las lecturas analógicas nunca son perfectamente quietas: aunque no toques el
// potenciómetro, el número "tiembla" un poco. a eso le llamamos ruido.
// usamos 3 trucos para eliminarlo:

// truco a: leer muchas veces seguidas y sacar el promedio.
const uint LECTURAS_POR_PROMEDIO = 16;

// truco b: suavizar. cada lectura nueva se mezcla con las anteriores,
// así un salto repentino casi no se nota. el número indica cuánto suavizamos:
// 1 = poco, 2 = medio, 3 = mucho (más suave, pero responde más lento).
const int SUAVIZADO = 2;

// truco c: zona muerta. solo aceptamos un cambio si el valor se movió
// al menos esta cantidad (en la escala de 0 a 4095).
const int ZONA_MUERTA = 6;

// ---------------------------------------------------------------------------
// 4. variables globales
// ---------------------------------------------------------------------------
// un arreglo (array) es una lista de valores. "[CANTIDAD_POTES]" significa que
// guarda 3 valores: uno por potenciómetro. se accede con un índice: [0], [1], [2].

int valorSuavizado[CANTIDAD_POTES];  // memoria del filtro de suavizado
int valorEstable[CANTIDAD_POTES];    // último valor aceptado (0 a 4095)

// ---------------------------------------------------------------------------
// 5. funciones
// ---------------------------------------------------------------------------
// una función es un bloque de código con nombre que podemos usar muchas veces.

// elige uno de los canales del multiplexor (0 a 7)
void elegirCanal(uint canal) {
    // "canal & 1" mira el primer bit del número del canal,
    // "(canal >> 1) & 1" mira el segundo bit y "(canal >> 2) & 1" el tercero.
    // ejemplo: canal 2 en binario es 010 -> S0 = 0, S1 = 1, S2 = 0
    gpio_put(PIN_S0, (canal >> 0) & 1);
    gpio_put(PIN_S1, (canal >> 1) & 1);
    gpio_put(PIN_S2, (canal >> 2) & 1);

    // esperamos 10 microsegundos para que el multiplexor termine de cambiar
    sleep_us(10);
}

// lee un canal y devuelve el promedio de varias lecturas (0 a 4095)
int leerCanal(uint canal) {
    elegirCanal(canal);

    // la primera lectura después de cambiar de canal puede salir mal,
    // así que la hacemos y no la guardamos
    adc_read();

    // sumamos varias lecturas...
    int suma = 0;
    for (uint i = 0; i < LECTURAS_POR_PROMEDIO; i++) {
        suma = suma + adc_read();
    }

    // ...y dividimos por la cantidad para obtener el promedio
    return suma / LECTURAS_POR_PROMEDIO;
}

// lee un potenciómetro, le quita el ruido y devuelve un valor de 0 a 99
int leerPote(uint numero) {
    int lectura = leerCanal(numero);

    // suavizado (truco b):
    // valorSuavizado guarda el valor multiplicado (por 4 si SUAVIZADO es 2).
    // en cada vuelta le sumamos la lectura nueva y le restamos una parte del
    // valor antiguo. el resultado es un promedio que se mueve de a poco.
    // ">>" divide por potencias de 2: x >> 2 es lo mismo que x / 4.
    valorSuavizado[numero] = valorSuavizado[numero] + lectura - (valorSuavizado[numero] >> SUAVIZADO);
    int valor = valorSuavizado[numero] >> SUAVIZADO;

    // zona muerta (truco c):
    // abs() da la diferencia sin signo (abs(-8) = 8).
    // si el valor cambió poco, lo ignoramos y mantenemos el anterior.
    // también aceptamos siempre los extremos (0 y 4095) para poder llegar a ellos.
    if (abs(valor - valorEstable[numero]) >= ZONA_MUERTA || valor == 0 || valor == ADC_MAXIMO) {
        valorEstable[numero] = valor;
    }

    // conversión de escala: de 0..4095 a 0..99.
    // multiplicamos por 100 y dividimos por 4096 (una más que el máximo).
    // así cada número de 0 a 99 corresponde a un tramo del mismo tamaño del pote.
    // ejemplo: 2048 (la mitad) * 100 / 4096 = 50
    return valorEstable[numero] * (VALOR_MAXIMO + 1) / (ADC_MAXIMO + 1);
}

// prepara pines y adc. se llama una sola vez al comienzo.
void configurar() {
    // activa la comunicación por usb para poder usar printf()
    stdio_init_all();

    // el pico 2 tiene una fuente de energía interna que genera un poco de ruido.
    // poniendo el gpio 23 en 1 la fuente trabaja en un modo más estable,
    // y las lecturas analógicas salen más limpias.
    gpio_init(23);
    gpio_set_dir(23, GPIO_OUT);
    gpio_put(23, 1);

    // los 3 pines del multiplexor son salidas: el pico les manda señales
    gpio_init(PIN_S0);
    gpio_init(PIN_S1);
    gpio_init(PIN_S2);
    gpio_set_dir(PIN_S0, GPIO_OUT);
    gpio_set_dir(PIN_S1, GPIO_OUT);
    gpio_set_dir(PIN_S2, GPIO_OUT);

    // prepara el adc y el pin donde llega la señal del multiplexor
    adc_init();
    adc_gpio_init(PIN_MUX_SALIDA);
    adc_select_input(ENTRADA_ADC);

    // primera lectura de cada pote, para que los filtros partan
    // desde la posición real y no desde cero
    for (uint i = 0; i < CANTIDAD_POTES; i++) {
        int lectura = leerCanal(i);
        valorSuavizado[i] = lectura << SUAVIZADO;  // "<<" multiplica: x << 2 es x * 4
        valorEstable[i] = lectura;
    }
}

// ---------------------------------------------------------------------------
// 6. programa principal
// ---------------------------------------------------------------------------
// main() es donde empieza el programa.

int main() {
    configurar();

    // "while (true)" repite el bloque para siempre
    while (true) {
        // leemos los 3 potes
        int pote0 = leerPote(0);
        int pote1 = leerPote(1);
        int pote2 = leerPote(2);

        // los mostramos en el monitor serial.
        // "%2d" significa: escribe un número entero usando 2 espacios,
        // así las columnas quedan alineadas. "\n" es un salto de línea.
        printf("pote0: %2d   pote1: %2d   pote2: %2d\n", pote0, pote1, pote2);

        // pausa de 50 milisegundos (unas 20 lecturas por segundo)
        sleep_ms(50);
    }
}
