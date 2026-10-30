## integrantes 

- ***Anais Marschhausen*** 
- ***Antonia Loch***
- ***Hugo Montoya***
- ***Carla Núñez***



## sobre el proyecto 

Este proyecto toma como referente el Apple Macintosh de 1984, recuperando su lenguaje visual basado en ventanas, carpetas, íconos y una interfaz monocromática de píxeles. A partir de esta estética, proponemos un escritorio digital interactivo que permite explorar fotografías y recuerdos personales de una manera intuitiva y cercana.
El proyecto busca reflexionar sobre cómo la tecnología, además de procesar información y facilitar tareas cotidianas, puede convertirse en un medio para preservar algo profundamente humano: los recuerdos, los vínculos y las experiencias compartidas.

## referente Apple Mac
El Macintosh 128K, lanzado en enero de 1984, destacó por incorporar una interfaz gráfica de usuario basada en ventanas, íconos y menús, junto con el uso de un ratón. Su pantalla monocromática de 1 bit representaba las imágenes mediante píxeles blancos y negros.
La tipografía y gran parte de la iconografía original fueron diseñadas por Susan Kare, cuyo trabajo contribuyó a que la informática resultara más accesible y comprensible para usuarios sin conocimientos técnicos.
Nuestro proyecto retoma este lenguaje visual y lo combina con un anacronismo consciente: ventanas simultáneas que funcionan como espacios de exploración y encuentro con recuerdos personales.

## concepto 
La propuesta consiste en un escritorio digital compuesto por cuatro carpetas que contienen imágenes personales simplificadas a frame. Mediante botones y perillas físicas, el usuario puede desplazarse por la pantalla, seleccionar carpetas y explorar sus fotografías.
La interacción busca ser sencilla e intuitiva, generando una experiencia íntima que acerque la tecnología a las personas. 

- **Escritorio:** inspirado en la interfaz gráfica del Macintosh de 1984.
- **Carpetas:** una cuadrícula de 2 × 2 con cuatro carpetas que contienen imágenes.
- **Ventanas:** elementos visuales que permiten mostrar el contenido de las carpetas.
- **Pantalla:** muestra el escritorio, las fotografías y las interacciones del usuario.
- **Estética:** píxeles, íconos y gráficos monocromáticos.

## interacción 

- **Perilla 1 (eje Y):** movimiento vertical en la pantalla
- **Perilla 2 (eje X):** movimiento horizontal, simulando el movimiento de un mouse
- **Botón 1:** seleccionar y abrir una carpeta
- **Botón 2:** controlar acciones relacionadas con la reproducción y visualización de imágenes

parte de nuestra clase: 

- **Sin presionar:** estado 0.
- **Presionar durante 1 segundo:** abrir la carpeta seleccionada.
- **Presionar 2 veces:** avanzar a la siguiente fotografía.
- **Presionar 3 veces:** activar un carrusel de fotografías.
- **Mantener presionado durante 5 segundos:** volver al escritorio, independientemente de la posición de las perillas.

Al abrir una carpeta, se muestra inicialmente su primera imagen. El usuario puede avanzar entre fotografías y activar su reproducción secuencial. Una pulsación prolongada permite regresar al escritorio y explorar otra carpeta.

## desarrollo técnico 

El proyecto contempla la programación de clases para botones y perillas, responsables de traducir las acciones físicas del usuario en interacciones digitales.
La clase Boton considera cinco variables y cinco funciones para gestionar el estado del botón, detectar las pulsaciones, medir su duración y ejecutar acciones según el contexto de uso.
Las perillas permiten controlar la posición del cursor en los ejes horizontal y vertical, mientras que la pantalla representa visualmente las acciones realizadas.
Se considera el uso de una Raspberry Pi como plataforma de procesamiento y almacenamiento, junto con una pantalla y controles físicos. Las imágenes se organizan en carpetas para facilitar su navegación y visualización.

## diagrama de flujo 
![imagenes](./imagenes/diagrama.png)
