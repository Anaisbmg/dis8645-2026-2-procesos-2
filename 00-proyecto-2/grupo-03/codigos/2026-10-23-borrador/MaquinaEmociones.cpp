#include "MaquinaEmociones.h"

void MaquinaEmociones::encender()
{
    MaquinaEmociones::prendida = true;
}

void MaquinaEmociones::apagar()
{
    MaquinaEmociones::prendida = false;
}

void MaquinaEmociones::cambiarModo(bool avanzar) {}

void MaquinaEmociones::actualizarEmocionDificultad() {}

void MaquinaEmociones::actualizar() {}