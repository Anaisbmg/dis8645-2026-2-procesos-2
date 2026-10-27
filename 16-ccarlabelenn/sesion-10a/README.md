# sesion-10a

## apuntes sesión
esta sesión fue remota y se caía el cielo, en lo personal no asistí ya que estuve en procedimientos médicos. 
![imagenes](./imagenes/secae.jpeg)

no nos unimos a la reunión pero nos pusimos de acuerdo con la idea que tenemos para nuestro proyecto, pediremos revisión el viernes 23.


**Referente del proyecto:** Apple Macintosh (1984)

### 2. Definimos el concepto

- Buscamos el significado de **anacronismo consciente**: incluir a propósito un objeto, una tecnología o una idea que no corresponde a la época de una obra, con un fin estético, narrativo o crítico.
- Lo aplicamos así: *tomamos el lenguaje visual de 1984, pero con ventanas simultáneas, como los accesorios de escritorio.*
- **Bajada del proyecto:** busca crear un escenario más íntimo, personal y cercano. Queremos usar la tecnología, que es fundamental en nuestras vidas, como un medio para preservar algo intensamente humano.

### 3. Idea inicial

La propuesta fue un computador viejo donde los videos de nuestros seres queridos, o videos que grabemos nosotros, sean **carpetas**, de modo que se puedan abrir varias a la vez y aparezcan varias ventanas en la pantalla. Para los controles, pensé en un botón para seleccionar una carpeta, otro para reproducir, y perillas que sirvan para navegar como si fueran un mouse. En ese momento no sabía si era posible lograrlo con perillas, así que lo dejamos planteado como idea para investigar.

### 4. Definimos cómo funciona

El proyecto funciona como un escritorio de computador con una **cuadrícula de 2 × 2**, es decir, cuatro carpetas con imágenes dentro:

| Elemento | Función |
|---|---|
| Botón 1 | Seleccionar la carpeta |
| Botón 2 | Reproducir (en la versión final, el carrusel de fotos) |
| Perilla 1 | Moverse por la pantalla en el eje Y |
| Perilla 2 | Moverse por la pantalla en el eje X |
| Pantalla | Muestra el escritorio y el contenido seleccionado |

### 5. Trabajo con las clases Boton y Perilla

Nos pidieron crear clases. A nuestro grupo le tocó **Boton**, y al otro grupo, **Perilla**. Cada clase tiene que servirle a los dos grupos, así que la clase Boton no puede depender de un solo proyecto. Definimos qué gestos debía reconocer:

Para la clase anoté qué debe saber hacer un botón: ser presionado, soltarse y medir el tiempo que estuvo presionado.

---

## ¿Qué aprendí?

- Que la gran novedad del Macintosh fue la **interfaz gráfica**: ventanas, íconos y menús manejados con un mouse de un solo botón.
- Qué es un **anacronismo consciente** y cómo usarlo como decisión de diseño.
- Que una clase pensada para varios grupos debe **separar la detección** (cómo se presionó) del **significado** (qué se hace después).
- Que un botón se puede describir con **estados** (no presionado, presionado) y con el tiempo que está presionado.
- Que existen distintos tipos de memoria y que no todas las placas usan los mismos. 

---

## Pendientes

- Agregar a la clase Boton el gesto de **5 segundos** para volver al escritorio.
- Acordar con el grupo de Perilla los nombres de los métodos.
- Decidir la pantalla
- Definir cómo convertir las imágenes a píxeles

## encargos

## lectura
