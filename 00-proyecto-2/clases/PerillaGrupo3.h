#ifndef PERILLA_H
#define PERILLA_H

class Perilla
{

public:
    ////////////
    // atributos
    ////////////

    // identifica la entrada analógica
    int pin;

    // almacena la posición actual
    int valor = 0;

    // define cuántas opciones puede seleccionar
    int cantidadOpciones;

    int opcionSeleccionada;

    // 0 de emocion
    // 1 de navegacion
    int tipo;

    //////////////
    // constructor
    //////////////

    Perilla(int nuevoPin, int nuevoTipo);

    //////////
    // metodos
    //////////

    // decide cuantas opciones posibles
    void definirOpciones(int numeroOpciones);

    // obtiene el valor analógico del potenciómetro.
    void leerValor();

    // convierte el valor obtenido en una opción determinada
    void calcularOpcion();
};

//////
// uso
//////

///////////////////////////
// esto ocurre al principio
///////////////////////////

// declara una instancia de la perilla
// se configuran las opciones

/////////////////
// constantemente
/////////////////

// se hace la lectura analogica
// y esto actualiza la opcion
// luego puedo consultar la opcion

#endif