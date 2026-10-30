// Boton2.cpp
// En Boton2.h dijimos QUÉ es un botón (atributos) y QUÉ puede hacer (funciones)
// Aquí escribimos CÓMO lo hace
// Solo usamos lo que está declarado en el .h.

#include "Boton2.h"   // trae la clase que declaramos en el .h

// CONSTRUCTOR
// Se ejecuta una sola vez, cuando creamos el botón en el main
//      Boton2 miBoton queda en el pin 14
// El 14 llega aquí en la variable "pin"

Boton2::Boton2(int pin)
{
    // Guardamos el número del pin dentro del botón
    // "this->pin" es el atributo del .h; "pin" es el número que nos pasaron.
    this->pin = pin;

    // Preparamos el pin de la Pico
    gpio_init(this->pin);              // enciende el pin
    gpio_set_dir(this->pin, GPIO_IN);  // lo deja como encendido 
    gpio_pull_up(this->pin);           // sin apretar 1, apretado 0
                                       // (por eso el botón se conecta entre el pin y GND)
}


// leer()
// Se llama en cada vuelta del while(true) del main.
// Mira el botón y va avanzando por los estados:
//      REPOSO -> PRESIONADO -> ESPERANDO_PRESION
// Cuando reconoce un gesto, lo deja guardado en gestoPendiente.
void Boton2::leer()
{
    // Milisegundos desde que se encendió nuestro reloj
    uint32_t ahora = to_ms_since_boot(get_absolute_time());

    // Lee el pin. Como apretado = 0, lo damos vuelta con "!"
    // Así "lectura" es true cuando el botón está apretado
    bool lectura = !gpio_get(pin);

    // Comparamos con lo que había antes (presionado) para saber qué pasó
    bool apretaron = (!presionado && lectura);   // antes suelto, ahora apretado
    bool soltaron = (presionado && !lectura);    // antes apretado, ahora suelto

    switch (estado)
    {
        
        // REPOSO: no está pasando nada.
        case EstadoBoton::REPOSO:
            if (apretaron)
            {
                estado = EstadoBoton::PRESIONADO;
                numeroPresiones = 0;
            }
            break;

      
        // PRESIONADO: el botón está apretado.
        
        case EstadoBoton::PRESIONADO:
            if (soltaron)
            {
                // Cuando se dejó de presionar, sabremos cuanto tiempo estuvo presionado
                // (ahora - instanteCambio) = tiempo desde que lo apretaron
                if (ahora - instanteCambio >= tiempoLargo)
                {
                    // se mantuvo 1 segundo o más pero menos de 5 (pulsación larga)
                    gestoPendiente = Gesto::PULSACIONLARGA;
                    numeroPresiones = 0;
                    estado = EstadoBoton::REPOSO;
                }
                else
                {
                    // se mantuvo un segundo pulsación corta, lo contamos como un clic
                    // y esperamos una próxima pulsación 
                    numeroPresiones++;
                    estado = EstadoBoton::ESPERANDO_PRESION;
                }
            }
            else if (lectura && (ahora - instanteCambio >= tiempoMuyLargo))
            {
                // si lleva presionado más de 5 segundos (pulsación muy larga)
                gestoPendiente = Gesto::PULSACIONMUYLARGA;
                numeroPresiones = 0;

                // vuelve a REPOSO aunque se siga apretando el botón
                // este gesto se informa una sola vez
                // en REPOSO solo reaccionamos cuando lo vuelven a apretar
                estado = EstadoBoton::REPOSO;
            }
            break;


        // ESPERANDO_PRESION: se soltó el botón y esperamos
        // (tiempoEntrePresionado) se espera una próxima pulsación
        
        case EstadoBoton::ESPERANDO_PRESION:
            if (apretaron)
            {
                // pulsación a tiempo: se sigue contando (no se borra numeroPresiones)
                estado = EstadoBoton::PRESIONADO;
            }
            else if (ahora - instanteCambio >= tiempoEntrePresionado)
            {
                // sin pulsaciones: decidimos qué gesto fue
                if (numeroPresiones == 1)
                {
                    gestoPendiente = Gesto::PULSADO1VEZ;
                }
                else if (numeroPresiones == 2)
                {
                    gestoPendiente = Gesto::PULSADO2VECES;
                }
                else if (numeroPresiones == 3)
                {
                    gestoPendiente = Gesto::PULSADO3VECES;
                }
                // con 4 pulsaciones o más no pasa nada

                numeroPresiones = 0;
                estado = EstadoBoton::REPOSO;
            }
            break;
    }

    // Al final de cada vuelta guardamos cómo quedó el botón
    presionado = lectura;

    // Si el botón cambió (lo apretaron o lo soltaron), anotamos la hora del cambio
    if (apretaron || soltaron)
    {
        instanteCambio = ahora;
    }
}


// leerGesto()
// main llama para saber si pasó algo.
// Entrega el gesto guardado y lo borra, para no leerlo dos veces.
Gesto Boton2::leerGesto()
{
    Gesto gesto = gestoPendiente;     // copiamos el gesto guardado
    gestoPendiente = Gesto::NADA;     // borramos el original
    return gesto;                     // entregamos la copia
}
