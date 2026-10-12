# sesion-08a

06-10-2026

## apuntes sesión

Lógica de las clases - Muchas cosas

para modelar o crear

Personas y 1 que se llama Kris

Matías también se llama Misaa - nombre artístico

Atributos y métodos son los que están adentro de las clases, forma o función

en este curso nos vamos a alejar del modelar un poco y nos concentraremos en crear

hay que ahorrar espacio, optimizar programación y hay un factor de mantención Constructor

### vamos a hacer una clase de LED

Clase Lucecita

tiene un estado que se llama encendido y un conjunto de valores (resumido) que pueden ser SÍ o NO

hay un conjunto de valores que puede decir cuán encendido está y puede llamarse brillo ej: de 0 a 255 y luego elegimos en qué valor de ahí para arriba o para abajo está encendido y cuál no, que se llama UMBRAL

Parpadeo: -tiempo LuzNavidad = Lucecita [100];

Los arreglos están en orden

hay color = rojo, verde, azul

va a haber un Usuario y una Lucecita y otro Botón y van a ser clases

Puede haber otra clase que se llame EspantaCuco

int precio;

"instancia de clase - es haber usado el molde que llamamos Lucecita y crear una de ellas" Lucecita espantadora;

Sensor lumínico;

puede pasar que Lucecita sea algo tan abstracto en el sentido de lejano y no de difuso (reducir la complejidad a algo de una sola expresión)

Clase helado
int precio
cremosidad
vegano

class HeladoChirimoya {

heredó Helado; cremosidad de la Chirimoya = 100%;

## encargos

encargo-08a:

1. tomar muchas fotos, mínimo 3 por cada uno de los 3 elementos que estudiamos hoy: perillas, botones, y luces. subir las fotos a su README como respuesta a este encargo, y describirlas textualmente, para con esa info complejizar nuestras clases programadas este viernes.

2. partir del ejemplo de hoy, que está subido en codigos/ de hoy, y hacer que las luces parpadeen. para eso, definir parpadeo de forma paramétrica.

### Solución ercargo 1.


| Imagen | Descripción |
|:---:|:---|
| ![Perilla giratoria 1](imagenes/perilla_giratoria_1.png) | Es un círculo extruido hacia otro círculo de menor radio, con una diferencia aproximada de 0,4 mm entre ambos. La extrusión tiene una longitud de aproximadamente 2 cm. En la superficie lateral presenta surcos cada 1 mm y, desde el centro de la cara superior, una línea blanca que se extiende hasta el borde exterior de la perilla. |
| ![Perilla giratoria 2](imagenes/perilla_giratoria_2.png) | Círculos del mismo tamaño, extruidos aproximadamente 2 cm, con una línea blanca que recorre el centro hasta el borde exterior. Presenta surcos distribuidos cada 4 mm aproximadamente por toda la superficie lateral. |
| ![Perilla giratoria 3](imagenes/perilla_giratoria_3.png) | Círculo extruido 3 mm hasta formar otro del mismo tamaño. En ese punto presenta un relieve diagonal uniforme que se dirige hacia el interior, formando un nuevo círculo de menor tamaño, ubicado aproximadamente a la mitad del radio del primero. Desde este tercer círculo se desarrolla una segunda extrusión diagonal, menos pronunciada, que alcanza una longitud aproximada de 1,5 cm y termina en un círculo aún más pequeño. Esta segunda extrusión presenta surcos verticales cada 1 mm aproximadamente, mientras que las demás superficies son lisas. |


| Imagen | Descripción |
|:---:|:---|
| ![Botón 1](imagenes/boton_1.png) | Círculo pulsable hacia adentro de color rojo, creado sobre una superficie cilíndrica que lo rodea. Debajo tiene una superficie cuadrada extruida que hace de base, con un tornillo en la base y no en el círculo ni en el cilindro, para unir las piezas. |
| ![Botón 2](imagenes/boton_2.png) | Círculo rojo extruido que sobresale de un soporte semicircular con surcos en el borde cada 1 mm aprox. Soporte metálico con una parte inferior que está envuelta por plástico y de la cual sobresalen 2 patitas metálicas, una a cada lado. |
| ![Botón 3](imagenes/boton_3.png) | Círculo de poca extrusión de color rojo que en el centro tiene un palito que lo une a una caja inferior que funciona como mecanismo, pero está oculto por la caja. Los círculos exteriores extruidos mencionados anteriormente se pueden empujar hasta que choquen con la caja que tienen debajo. Tiene 3 flechas curvas en la cara exterior del primer círculo, que son de color blanco, de unos 3 mm de grosor aprox. y van en el sentido de las agujas del reloj, con un leve espacio entre ellas, siguiendo una a la otra y formando un casi círculo que va en una dirección. En la parte inferior del palo, pero antes de llegar a la caja, tiene en su borde surcos cada 1 mm aprox. |


| Imagen | Descripción |
|:---:|:---|
| ![Luz 1](imagenes/luz_1.png) | Brillo envuelto por una cúpula curva en su inicio y recta hasta llegar a la superficie de soporte de 1 cm aprox. de largo, con 2 patitas de metal que sobresalen del centro, pero separadas entre sí y una más larga que la otra. |
| ![Luz 2](imagenes/luz_2.png) | Tira de plástico negro con cuadrados dispuestos sobre una cara de la tira, separados entre sí por 1 cm aprox. Entre ellos hay chips pequeños, círculos o cuadrados más pequeños, pero de metal. |
| ![Luz 3](imagenes/luz_3.png) | Rectángulo robusto y extruido. En una de sus 2 caras, en la parte larga y ancha, tiene muchos círculos que sobresalen en el interior y que son LED. Los bordes son anchos, con algunas hendiduras largas y sutiles en los 4 bordes más cercanos al exterior de la misma cara para el agarre. Los círculos exteriores están dispuestos en una grilla de 40 por 20, con espacio entre cada circulito LED. |


### Solución ercargo 2.

Ya quedó listo el parpadeo por medio de la perilla y está subido a la carpeta de códigos de esta sesión.

## lectura

Se presenta Scratch 3 como una forma más sencilla de comenzar a programar en Raspberry Pi. Diferente de otros lenguajes donde hay que escribir instrucciones, en Scratch se utilizan bloques de colores que se van uniendo para crear programas. También se explica su interfaz, donde aparecen partes como el escenario, los objetos, la lista de objetos, la paleta de bloques y el área de código.

Después se muestra cómo hacer el primer programa en Scratch. Para esto se utiliza el bloque “decir ¡Hola!” y se une con el bloque que se activa al hacer clic en la bandera verde. Los bloques funcionan como piezas de un rompecabezas, ya que se pueden arrastrar y unir entre ellos. Al presionar la bandera verde, el gato de Scratch ejecuta el programa y dice “¡Hola!”.

En las pág. 58 y 59 se explica que antes de continuar es recomendable ponerle un nombre al programa y guardarlo. Después se comienza a trabajar con la secuenciación, donde las instrucciones se ejecutan una después de otra. Como hacer que el gato avance 10 pasos, reproduzca un sonido y luego retroceda 10 pasos.

Y en la pág. 60 se prueba esta secuencia con la bandera verde. También se muestra que el programa se puede modificar cambiando el orden de los bloques. Por ejemplo, se puede colocar una espera de 1 segundo para que las acciones no sean tan rápidas y sea más fácil notar lo que está pasando en la pantalla.

2 Citas:

1. “Scratch construyes tu programa paso a paso utilizando bloques”.

2. “Los programas informáticos, incluso los más simples, se componen de una lista de instrucciones”.
   
Pregunta:

¿Por qué en Scratch es importante el orden en que se colocan los bloques dentro de una secuencia?

Referente:

Scratch 3 y su forma de programación mediante bloques, incluyendo su interfaz, el uso de objetos, el área de código, la creación de un primer programa y la organización de instrucciones en una secuencia.
