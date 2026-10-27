// TRAZO — código 1: primero ordenamos lo que queremos que pase.
// Esta versión tiene sólo comentarios. Todavía no es un programa ejecutable.
// Vamos a trabajar con Raspberry Pi Pico RP2040 y C/C++ con Pico SDK.
//
// 0. QUÉ QUEREMOS HACER
// Queremos mover un cursor con dos perillas en una pantalla OLED de 128 x 64.
// Una mueve X y la otra Y, cada una por su lado.
// Más adelante, con TRAZO vamos a alternar entre MOVER y DIBUJAR.
// Con BORRAR vamos a limpiar el dibujo y volver a MOVER.
// Los botones quedan pendientes de la clase Boton que nos mandará el otro grupo.
// Por ahora sólo están en el diagrama, como referencia de lo que vamos a conectar.
//
// 1. PREPARAR ENTRADAS Y RANGOS
// Nos basamos en el ejemplo de Perilla de los profes de la sesión 08a.
// En Perilla.h vamos a declarar la clase y en Perilla.cpp explicar cómo funciona.
// Cada perilla va a guardar su patita, lectura, posición y máximo.
// Iniciamos el ADC una sola vez en main, antes de crear las perillas.
// GP26 corresponde a ADC0, GP27 a ADC1 y GP28 a ADC2.
// Ojo: estos nombres son GPIO, no la numeración física de las patitas de la placa.
// Antes de leer, elegimos el canal de esa perilla para no mezclar los dos ejes.
// El ADC entrega de 0 a 4095. Son 4096 valores, pero el último es 4095.
// Para X usamos 0..127 y para Y 0..63, porque empezamos a contar desde cero.
// Multiplicamos antes de dividir, así no perdemos la fracción demasiado pronto.
// Usamos un valor intermedio suficientemente grande para que la cuenta no se desborde.
// Para el otro grupo separamos el volumen (Perilla) de la selección (Encoder).
// El potenciómetro entrega una lectura analógica; el encoder entrega pasos y dirección.
//
// 2. PREPARAR PANTALLA Y TIEMPOS
// Primero preparamos la comunicación, el ADC, el I2C y la pantalla.
// Leemos la posición inicial antes de dibujar, para no crear una línea desde (0,0).
// 3. LEER, ACTUALIZAR Y MOSTRAR
// Después repetimos: leer entradas, decidir qué pasó, actualizar y mostrar.
// Con time_us_64 medimos los intervalos sin poner sleep_ms en el ciclo principal.
// Eso no significa que todo sea instantáneo: enviar la imagen por I2C toma tiempo.
//
// 4. INTEGRAR DIBUJO Y BOTONES (MÁS ADELANTE)
// En MOVER, el cursor se mueve sin dejar marcas en el dibujo.
// En DIBUJAR, unimos la posición anterior con la actual para que el trazo siga continuo.
// Al empezar un trazo nuevo, actualizamos la posición anterior con la posición actual.
// Así evitamos que aparezca un puente entre dos dibujos separados.
// Guardamos el dibujo aparte del cursor y del indicador, para no borrarlo al movernos.
// Si llegan TRAZO y BORRAR juntos, primero resolvemos BORRAR.
// Después de borrar, limpiamos el dibujo, volvemos a MOVER y sincronizamos la posición.
// Mantener un botón apretado debería generar una sola acción, según el acuerdo de Boton.
// Todo esto es el plan de integración; las versiones 2 y 3 todavía no lo implementan.
//
// 5. REVISAR RESULTADOS
// Movemos una perilla a la vez y comprobamos que la otra coordenada se mantenga.
// Probamos los extremos, la mitad y los bordes de la pantalla.
// Separamos las pruebas en computador de la compilación Pico y la simulación Wokwi.
// Anotamos lo que realmente pasó, el error y la corrección, con su evidencia.
// En cada prueba anotamos qué pasó, qué esperábamos y cómo resolvimos la diferencia.
// Dejamos una carpeta por versión para poder revisar cómo fue avanzando el código.
