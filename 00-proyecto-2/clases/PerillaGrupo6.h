//promesas de lo que queremos que las perillas hagan
//para las perillas usaremos

//perilla1 controla la velocidad con la que 
//el mapa se desplaza en el eje x
//el usuario no debe mantener en mov la perilla
//constantemente
//puede dejarla quieta en un punto
//para utilizar esa velocidad 
//es un umbral de velocidad
//va desde muy lento
//a muy rapido


//perilla2 se mueve entre los personajes 
//para seleccionar alguno
//existen 4 opciones
//eso seria
//KLSDFLKS


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
