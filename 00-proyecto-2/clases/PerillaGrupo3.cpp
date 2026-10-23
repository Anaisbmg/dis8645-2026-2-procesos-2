#include "PerillaGrupo3.h"

Perilla::Perilla(int nuevoPin)
{
    Perilla::pin = nuevoPin;
}

//////////
// metodos
//////////

// decide cuantas opciones posibles
void Perilla::definirOpciones(int numeroOpciones)
{
    Perilla::cantidadOpciones = numeroOpciones;
}

// obtiene el valor analógico del potenciómetro.
void Perilla::leerValor()
{
    // lee analogico segun raspi sdk
    // calcula la opcion
    Perilla::calcularOpcion();
}

// convierte el valor obtenido en una opción determinada
void Perilla::calcularOpcion()
{
    // toma el rango de entrada
    // 0 a 4093
    // y decide a cual opcion corresponde
    // esto tiene que ver con regla de 3
    // luego esto define la opcion
    Perilla::opcionSeleccionada = 0;
}
