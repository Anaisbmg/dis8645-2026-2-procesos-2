#ifndef TRAZO_ENCODER_H
#define TRAZO_ENCODER_H
// El encoder nos entrega pasos y dirección, por eso lo leemos distinto al potenciómetro.
class Encoder {
public:
    int direccion = 0; // Vale -1, 0 o +1. Ojo: corresponde a esta lectura, no queda fijo.
    int posicion = 0;  // Aquí guardamos la opción elegida. Si son cinco sonidos, contamos de 0 a 4.
    bool valida = false;
    Encoder(unsigned int clk, unsigned int dt, int cantidad = 5, bool invertir = false);
    void leer();
    void procesar(bool clk, bool dt); // Con esto podemos probar los pasos sin conectar el encoder.
private:
    unsigned int clk_, dt_;
    int cantidad_, anterior_ = 3, acumulado_ = 0;
    bool invertir_;
};
#endif
