# Proyecto 2 

**Integrantes:**


- Belén Castillo / [bombobby](https://github.com/bombobby) 


- Martina Fernandez / [pumpkinguurl](https://github.com/pumpkinguurl) 

- Maite Villarroel / [maiteev](https://github.com/maiteev) 


- Nacha Zamudio / [nachazamudio](https://github.com/nachazamudio)


# Idea de proyecto 
  Juego de nave, la cual hay que mantener volando por el mayor tiempo que pueda sin chocar con obstáculos ni caer al suelo. Tendrá 2 botones y 2 perillas para su uso, el primer botón, al mantenerse presionado durante 2 segundos, prende y apaga el juego, el segundo botón es el que sirve para mantener la nave volando, ya que al presionarlo la nave sube hasta que el botón se suelta y la nave comienza a caer, por lo que se debe intercalar el presionar y soltar para evitar que la nave caiga. Las perillas manejan dos aspectos distintos, la primera es una selección de diferentes naves para que el usuario escoja. La segunda perilla regula la velocidad de juego, pudiendo subir o bajar la dificultad para ajustarla a sus capacidades. 

Botón 1: servirá para encender y apagar la pantalla (tendrás que mantenerlo presionado por 2 segundos) y además funciona como botón seleccionador (apretandolo una vez)

Botón 2: si lo mantienes presionado el personaje sube y si lo sueltas cae (eje y)

Perilla 1: funcionará para controlar la velocidad con la que avanza el mapa (eje x) 

Perilla 2: funcionará para cambiar la selección de personajes. 

Si el jugador choca o se cae, el juego se reinicia. 

# Computador elegido 
**Apple iMac G3** 

Interfaz de usuario:

Este computador cambió por completo la forma de comprar de los usuarios. Antes de la llegada del iMac, la tecnología siempre manejó la misma estética: equipos sobrios, grises y rectangulares. Cuando Apple presentó el iMac, transformó la forma de vender en un momento clave, justo cuando muchísima gente compraba su primera computadora. Lanzar al mercado un equipo con variedad de colores y un diseño tan particular rompió con la frialdad de la industria de esa época.
A partir de ahí, los compradores ya no solo elegían una máquina por su funcionamiento, sino también por una estética que reflejaba su propia identidad y que se integraba como un objeto interesante en su espacio. Todo esto demostró un éxito rotundo, pasando de ver al usuario como un simple operador de tecnología a un consumidor cautivado por el diseño, e iniciando una era donde la conexión visual y la experiencia de uso pasaron a ser factores decisivos de compra.

----

¿Porque este computador?

steve jobs genio, se fue, apple a la bancarrota, vuelve, dice “no vamos a hacer lo mismo que todos”, innova, personaliza, llama la atención y pum dijo “pa los gustos los colores” y sacó los imac g3 full color escoja caserita, ¿qué hay debajo de toda esa carcasa? no se preocupe caserita aquí se lo mostramos ¿que no entiende nada? yo tampoco pero se ve de locos siono si

en palabras formales, nos llamó la atención lo innovadora de la propuesta que trajo steve jobs al regresar como CEO de apple luego de ser despedido, algo que hoy en día podemos tomar como “obvio” que es el hecho de tener un objeto personal que se ajuste más a nuestros gustos solo por el hecho de poder escoger el color haya podido causar tanto revuelo. Además, de la decisión estética de permitir que se vea el contenido electrónico del computador y de los tipos de conexiones que admitió este computador que eliminó el puerto de disquetes y el haber agregado el puerto de conexión para los cables de internet, algo que recién se venía expandiendo en la época.

a mi personalmente me gustan los mouse con formas raras, hubiese amado tener uno de esos mouse con los que probablemente me hubiese dolido la mano de una manera - pumpkinguurl

# Atributos/Metodos/Constructores 
 ```cpp
//constructor del botón
//boton1:
//botón seleccionador
//boton2: 
//botón de Movimiento

//métodos del botón
//boton1:
//puede encender
//puede apagar
//puede seleccionar
//tiempo de antirrebote 
//boton2:
//puede subir - se mueve en el eje y
// mientras no se aprieta, el personaje cae 

//atributos del botón
//boton1:
// noPresionado a estaSiendoPresionado
//está presionado por 2sg
//tiempoParaMantener (2000ms) 
//está encendido
//está apagado
//está presionado por menos de 2sg
//está seleccionando una opción

//boton2:
// noPresionado a estaSiendoPresionado
//está presionado 
//constructor de las perillas
//perilla1:
//perilla seleccionadora de 4 personajes
//número de patita, deduce a qué canal del lector analógico 
//perilla2: 
//Encargada de regular la velocidad del mapa / juego 
//Recibe el número del pin físico al que está conectada esta perilla 


//métodos de la perilla
//perilla1:
//Divide el rango total del potenciómetro entre el número de personajes. 
//calcular el tamaño que le toca a cada personaje en el giro. 
//Determina en qué "casilla" cae la lectura filtrada actual. 
//perilla2:
//Toma la lectura filtrada interna 
//Cuando la perilla está al mínimo (0.0), el mapa avanza a la velocidad mínima (por ejemplo, 20 píxeles por segundo). 
//Cuando la perilla está al máximo (1.0), el mapa avanza a la velocidad máxima (por ejemplo, 90 píxeles por segundo).
//En cualquier punto intermedio, calcula la velocidad proporcional exacta para acelerar o frenar el avance del escenario suavemente.

//atributos de la perilla
//perilla1:
//Para recordar en qué patita físicamente está conectada la perilla y qué canal del lector analógico le toca consultar. 
//Un entero que recuerde qué opción (0, 1, 2 o 3) estaba seleccionada en la última comprobación.    
//perilla2:
//Un número entero que almacena la posición física limpia de la perilla tras procesar la señal del convertidor 

 ```
