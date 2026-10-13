# sesion-08b

## apuntes sesión
Clase vía zoom

###Primera parte

Revisión de encargos

Perillas, botones y luces

Parpadeo led wokwi


###Segunda parte


partimos con un psuedo código

vamos a tener un botón, el botón va a tener estados

noPresionado, estaSiendoPresionado, soltado

va a tener un atributo que será umbral de tiempo presionado, como el botón del gym que debes mantener 2 segundos apretados para que llegue un profesor a ayudarte

eso va a impactar en una luz LED

ese LED va a estar apagado siempre

cuando la persona presione entre 0 y 2sg va a prenderse de a poquito

cuando la persona supere el umbral de 2sg va a emitir la palabra hola en morse . . . . / - - - / . - . . / . - 

ponerse de acuerdo en lo que queremos hacer es mucho mas importante, declarar siempre

vamos a partir por el funcionamiento de la luz, luego le agregaremos el botón.

en lucecita.h vamos a tener que agregar mas métodos, vamos a tener que hacer una función puntito y una función raya para el código morse

en el main agregamos 

#Lucecita.h

instanciar una luz que es de la clase lucecita

Lucecita luz (7);

en el h ya no tenemos solo que prender y apagar, agregamos

void rampear();

ir de mínimo a máximo 

ahora vamos al cpp para hacernos cargo de esa promesa

void Lucecita::rampear(){

aquí tenemos un problema, la luz no sabe que tan prendida/apagada esta

en h agregamos 

int intensidad = 0;

la intensidad de la luz cuando parte es 0

cpp

void Lucecita::rampear() {
 Lucecita::intensidad = Lucecita::intensidad + 1;

esto permite que va a subir de a poco

main.c

luz.rampear(); 

y va a rampear

el problema que tiene esto es que ira subiendo infinitamente, debemos agregar un limite

en Lucecita.h agregamos

int minIntensidad = 0;
int maxIntensidad = 1024;

en cpp

if (Lucecita::intensidad > Lucecita::maxIntensidad) { 
  Lucecita::intensidad = Lucecita::maxIntensidad;

Pausa para prestar atención solamente y luego revisar la grabación

Necesito poder grabar mis pensamientos sobre lo que entiendo y lo que no porque escribirlos hace que me pierda de la explicación y esto es como si pestañeas pierdes y termino perdiéndome 

Se olvida la idea de rampear. Vamos a hacer void morsePunto y void morseRaya

morsePunto y morseRaya son iguales, lo único que cambia es la duración de cada uno

int duracionPunto = 200;

int duracionRaya: 1000;

en raspi se usa sleep_ms que en Arduino es equivalente a delay()

para usarlo debemos agregar una biblioteca #include pico/stdlib.h

hay que agregar otro int de la separación de los caracteres

```cpp

void Lucecita::morsePunto() {
  // prender
  gpio_put(Lucecita::patita, 1);
  // mantener prendido
  sleep_ms(Lucecita::duracionPunto);
  // apagar
  gpio_put(Lucecita::patita, 0);
  // pausa entre caracteres
  sleep_ms(Lucecita::duracionEntreCaracteres);
}

``` 
le pedimos a Claudio que nos arme el comando para ejecutar la palabra hola 

el ; nos permite escribir hacia al lado o hacia abajo, ya que significa que lo que viene después de eso es otra línea

```cpp

 luz.morsePunto();
   luz.morsePunto();
   luz.morsePunto();
   luz.morsePunto();
   luz.finLetra();

  // O  ---
  luz.morseRaya();
  luz.morseRaya();
  luz.morseRaya();
  luz.finLetra();

  // L  .-..
  luz.morsePunto();
  luz.morseRaya();
  luz.morsePunto();
  luz.morsePunto();
  luz.finLetra();

  // A  .-
  luz.morsePunto();
  luz.morseRaya();
  luz.finPalabra();

```

Claudio nos agrego la función luz.finLetra() y luz.finPalabra entonces debemos agregarlos 

```cpp

void Lucecita::finLetra() {
   sleep_ms(2 * Lucecita::duracionPunto);
  }

  // esperar 6 veces lo que dura el punto
  void Lucecita::finPalabra() {
    sleep_ms(6 * Lucecita::duracionPunto);
  }

```
"casi todos mis sueños caben en un botón" - Aarón Montoya, 2026

## encargos

## lectura
