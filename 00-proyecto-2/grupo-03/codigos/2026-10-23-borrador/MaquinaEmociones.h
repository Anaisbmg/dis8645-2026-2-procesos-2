#ifndef MAQUINA_EMOCIONES_H
#define MAQUINA_EMOCIONES_H

#include "PerillaGrupo3.h"

class MaquinaEmociones
{

    ////////////
    // atributos
    ////////////

    bool prendida;

    // perilla conectada a GP8, por ejemplo
    // segundo param es 0 porque emocion
    Perilla perillaEmociones(8, 0);

    // perilla conectada a GP10, por ejemplo
    // segundo param es 1 porque navegacion
    Perilla perillaNavegacion(10, 1);

    // SSD1306 pantalla;

    //////////////
    // constructor
    //////////////

    //////////
    // metodos
    //////////

    void encender();
    void apagar();
    // con avanzar true, avanza
    // con avanzar false, retrocede
    void cambiarModo(bool avanzar);
    void actualizarEmocionDificultad();
    void actualizar();
};
#endif