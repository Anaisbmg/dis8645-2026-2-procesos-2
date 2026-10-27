# sesion-10b

## 1. Concepto del proyecto

El proyecto consiste en crear una experiencia interactiva inspirada en el Apple Macintosh de 1984, utilizando su lenguaje visual para generar un espacio digital íntimo y personal.

La idea es utilizar la tecnología como un medio para preservar recuerdos y acercar a las personas a sus fotografías y videos de una manera sencilla, sin necesidad de tener conocimientos informáticos.

## 2. Interfaz del sistema

- **Escritorio:** inspirado en la interfaz gráfica del Macintosh de 1984.
- **Carpetas:** una cuadrícula de 2 × 2 con cuatro carpetas que contienen imágenes.
- **Ventanas:** elementos visuales que permiten mostrar el contenido de las carpetas.
- **Pantalla:** muestra el escritorio, las fotografías y las interacciones del usuario.
- **Estética:** píxeles, íconos y gráficos monocromáticos.

## 3. Controles físicos

El sistema utiliza perillas y botones para navegar por el escritorio.

- **Perilla 1 (eje Y):** movimiento vertical en la pantalla.
- **Perilla 2 (eje X):** movimiento horizontal, simulando el movimiento de un mouse.
- **Botón 1:** seleccionar y abrir una carpeta.
- **Botón 2:** controlar acciones relacionadas con la reproducción y visualización de imágenes.

El desarrollo se divide entre los grupos: nuestro grupo trabaja en las clases de botones y el otro grupo desarrolla las clases de las perillas.

## 4. Interacción con los botones

Se propone utilizar la duración y la cantidad de pulsaciones para ejecutar distintas acciones.

- **Sin presionar:** estado 0.
- **Presionar durante 1 segundo:** abrir la carpeta seleccionada.
- **Presionar 2 veces:** avanzar a la siguiente fotografía.
- **Presionar 3 veces:** activar un carrusel de fotografías.
- **Mantener presionado durante 5 segundos:** volver al escritorio, independientemente de la posición de las perillas.

Si el cursor no está sobre una carpeta y se intenta abrirla, no debe suceder nada.

Al abrir una carpeta, se muestra la primera fotografía de su contenido.

### Variables propuestas

- `estado`: indica si el botón está presionado.
- `tiempoInicio`: registra el momento en que comienza la presión.
- `duracion`: calcula cuánto tiempo se mantiene presionado.
- `contadorPulsaciones`: registra la cantidad de pulsaciones.
- `ultimaPulsacion`: registra el momento de la última pulsación.

### Funciones propuestas

- `presionar()`: detecta cuándo se presiona el botón.
- `soltar()`: detecta cuándo se libera.
- `calcularDuracion()`: calcula el tiempo de presión.
- `detectarPulsaciones()`: identifica pulsaciones simples, dobles o triples.
- `ejecutarAccion()`: ejecuta la acción correspondiente.

## 6. Aspectos técnicos por desarrollar

- Integración de los botones con las perillas.
- Navegación entre las cuatro carpetas.
- Visualización de fotografías en la pantalla.
- Implementación del carrusel de imágenes.
- Evaluación de la reproducción de videos y la incorporación de audio.
- Investigación sobre la conversión de fotografías y videos a una estética pixelada.
- Revisión de la memoria RAM y el almacenamiento de la Raspberry Pi.

## 7. Objetivo del proyecto

Desarrollar una interfaz física y digital que permita explorar recuerdos personales de forma sencilla e intuitiva, combinando una estética tecnológica retro con una experiencia humana, cercana y accesible.
