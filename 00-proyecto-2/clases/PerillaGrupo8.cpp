// Perilla.cpp
// Este archivo define la clase Perilla y sus metodos
// (declaracion e implementacion en un solo archivo)
// desarrollado por: Grupo 8
//

// stdint.h trae los tipos de tamano fijo
// por ejemplo uint16_t (entero sin signo de 16 bits)
// e int32_t (entero con signo de 32 bits)
#include <stdint.h>

// pico/stdlib.h trae las funciones basicas de la Raspberry Pi Pico
#include "pico/stdlib.h"

// hardware/adc.h trae las funciones del ADC
// ADC deglosado es Analog to Digital Converter
// o conversor analogico-digital: convierte un voltaje
// (de 0 a 3.3 V) en un numero entre 0 y 4095
#include "hardware/adc.h"

// ---------------------------------------------------
// DECLARACION DE LA CLASE
// ---------------------------------------------------

// Vamos a tener dos perillas.
//
// Ambas funcionan de la misma manera,
// pero cada una tendra su propio pin.
//
// Esta clase solo lee la perilla
// y convierte su lectura a otro rango.
//
// Mas adelante usaremos esos valores
// para controlar el lapiz de la pantalla.

class Perilla {
public:
    // IMPORTANTE
    // Esta clase funciona solo con los GPIO 26 y 27 (GP26 y GP27),
    // que son los unicos pines con ADC en esta primera version.
    // El ADC compartido se debe inicializar en main.cpp
    // (adc_init()) ANTES de llamar a iniciar() y leer().
    // La senal de la perilla nunca debe superar los 3.3 V,
    // revisar el circuito antes de conectar.
    // No nos responsabilizamos por danos en el hardware
    // si no se usa correctamente.

    // CONSTANTES
    // Evitan escribir numeros sueltos dentro del codigo.
    // Si cambia el hardware, se modifica solo aqui.

    // GPIO de la primera entrada ADC (GP26 es la entrada ADC 0)
    static constexpr unsigned int PRIMER_PIN_ADC = 26;

    // Lectura maxima del ADC de la Pico
    // El ADC es de 12 bits: 2^12 = 4096 valores, de 0 a 4095
    static constexpr uint16_t LECTURA_MAXIMA = 4095;

    // Cantidad de lecturas que se promedian en cada leer()
    // Sirve para filtrar el ruido, ya que el ADC "tiembla" un poco
    static constexpr int MUESTRAS = 8;

    // ATRIBUTOS
    // Son datos que guarda cada objeto.

    // GPIO donde conectamos la senal.
    unsigned int pin = 0;

    // Ultima lectura obtenida del ADC (promedio de MUESTRAS lecturas).
    uint16_t lectura = 0;

    // CONSTRUCTOR
    // Recibe el GPIO que usara esta perilla.
    Perilla(unsigned int pinADC);

    // METODOS
    // Son acciones que puede realizar el objeto.

    // Prepara el GPIO para una lectura analogica.
    void iniciar();

    // Lee la perilla y guarda el resultado.
    // Devuelve un numero entre 0 y 4095.
    uint16_t leer();

    // Convierte la ultima lectura guardada
    // al rango que necesitemos.
    int convertir(int minimo, int maximo);

    // METODOS ESPECIFICOS

    // Realiza una lectura y la convierte al rango pedido
    // leer() + convertir() = leerYConvertir()
    // Asi en main.cpp basta con una sola llamada.
    int leerYConvertir(int minimo, int maximo);
};

// ---------------------------------------------------
// IMPLEMENTACION DE LOS METODOS
// ---------------------------------------------------

// CONSTRUCTOR
// Se ejecuta cuando creamos un objeto Perilla.
// Guarda el GPIO recibido.
// Todavia no lee ni configura el hardware.
// lectura ya empieza en 0 porque se inicializa en la clase.
Perilla::Perilla(unsigned int pinADC) {
    // guardamos el pin recibido en el atributo del objeto
    pin = pinADC;
}

// INICIAR
// Prepara el GPIO para recibir una senal analogica.
// En esta primera version usaremos
// exclusivamente GP26 y GP27.
// El ADC compartido se inicializa en main.cpp.
void Perilla::iniciar() {
    // adc_gpio_init desconecta las resistencias digitales del pin
    // para que pueda medir voltajes analogicos sin interferencia
    adc_gpio_init(pin);
}

// LEER
// La Pico comparte un ADC entre varias entradas.
// Antes de leer, seleccionamos la entrada
// correspondiente a esta perilla:
// GP26 corresponde a la entrada ADC 0.
// GP27 corresponde a la entrada ADC 1.
// Por eso restamos 26 al numero del GPIO.
uint16_t Perilla::leer() {
    // seleccionamos la entrada ADC de esta perilla
    // pin - PRIMER_PIN_ADC es 0 para GP26 y 1 para GP27
    adc_select_input(pin - PRIMER_PIN_ADC);

    // suma acumula las lecturas, usamos uint32_t
    // porque 8 lecturas de hasta 4095 no caben en 16 bits
    uint32_t suma = 0;

    // tomamos MUESTRAS lecturas seguidas
    // ++ significa sumar 1, osea que i va de 0 a MUESTRAS - 1
    for (int i = 0; i < MUESTRAS; i++) {
        // adc_read devuelve un numero entre 0 y 4095
        suma += adc_read();
    }

    // el promedio de las lecturas es la suma entre la cantidad
    // asi filtramos el ruido del ADC
    lectura = suma / MUESTRAS;

    // devolvemos la lectura
    // return es una instruccion que devuelve un valor
    // y termina la accion de la funcion
    return lectura;
}

// CONVERTIR
// Usamos la lectura que guardo leer().
// Aqui no realizamos otra lectura.
// Ejemplo para el eje X:
// Lectura 0    es posicion 0.
// Lectura 4095 es posicion 319.
// Asi el recorrido completo de la perilla
// corresponde al recorrido completo del eje.
int Perilla::convertir(int minimo, int maximo) {
    // recorrido es el tamano total del rango de salida
    // por ejemplo de 0 a 319, el recorrido es 319
    // usamos int32_t porque lectura * recorrido
    // puede ser mas grande que lo que cabe en 16 bits
    int32_t recorrido = maximo - minimo;

    // regla de tres:
    // lectura / 4095 es la fraccion de giro de la perilla (de 0 a 1)
    // multiplicamos primero y dividimos al final
    // porque con enteros, dividir primero daria siempre 0
    // static_cast convierte lectura a int32_t
    // para que la multiplicacion se haga con el tamano correcto
    return minimo +
           (static_cast<int32_t>(lectura) * recorrido) / LECTURA_MAXIMA;
}

// LEER Y CONVERTIR
// Metodo que junta dos acciones en una sola.
// Primero lee la perilla y luego convierte el resultado.
int Perilla::leerYConvertir(int minimo, int maximo) {
    // actualizamos la lectura
    leer();

    // convertimos la lectura recien guardada
    // y devolvemos el resultado
    return convertir(minimo, maximo);
}
