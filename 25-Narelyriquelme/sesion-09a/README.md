# sesion-09a

## Apuntes sesión

Hoy partimos revisando lo que se pide para la entrega del proyecto 02 y después vimos KiCad con más profundidad. La idea es que esta semana y la próxima sean solo de dudas, para llegar preparadas a la gran entrega de fin de mes.

### Calendario

* **Próxima semana:** trabajo en clases y pasan lista a las 10.
* **Viernes 30:** entrega del proyecto 02.

---

### Proyecto 02: qué hay que entregar

Se trabaja en **grupos de 4**. Lo que se pide:

1. Escribir **una clase** (perilla o botón), que **otro grupo tiene que usar**.
2. Mínimo **2 perillas**.
3. **2 botones pulsadores** (se pueden sumar más botones, pero que no sean pulsadores).
4. Se puede usar la misma pantalla del proyecto 01.
5. **Carcasa** de cartón o impresión 3D.
6. Controlar **luz, sonido y pantalla**.
7. Hacer referencia a algún **PC pre 2010**: la máquina es un tributo a un computador antiguo.
8. Cuidar el lenguaje, los materiales y los colores.
9. Trabajar con el **lenguaje interfásico** (Mónica Jacobo, Gui Bonsiepe).
10. Tres diagramas:
    * **Usuario:** solo lo que ve el usuario.
    * **Software.**
    * **Hardware.**
11. **Prototipar en Wokwi.**

---

### KiCad

El semestre pasado, en el taller de Aaron y Misa, aprendimos a usar esta herramienta. **KiCad** sirve para diseñar esquemáticos (es un programa CAD, diseño asistido por computadora). Hoy lo vimos con más profundidad y trabajamos con el módulo de la Raspberry.

* **`.sch` (esquemático):** indica dónde están las conexiones y sus valores. No importa el diseño ni lo visual.
* **`.pcb`:** acá sí importa el diseño del esquema.
* Nunca olvidar **grabar**.

Cada componente tiene un **cuerpo** (el ícono), una **referencia** (la instancia, generalmente no se cambia) y un **valor** (la cantidad o el atributo, este sí se cambia).

| Componente | Cómo se llama en KiCad |
| --- | --- |
| Raspberry Pi Pico (la placa, no el chip solo) | `Module:RaspberryPi_Pico_Common_Unspecified` |
| Botón pulsador | `SW_Push` |
| Diodo LED | `D_LED` |

| Tecla | Qué hace |
| --- | --- |
| **A** | agregar símbolos y buscar componentes |
| **M** | mover solo el objeto (se desconecta) |
| **G** | mover el objeto manteniendo las conexiones |
| **V** | cambiar el valor o nombre |
| **T** | texto (documentación) |
| **L** | etiquetas de red |
| **Ctrl + D** | duplicar copiando los atributos |

* Un **cuadrado verde** significa que el componente no está conectado.
* A las conexiones que no van se les pone una **X**.
* En la entrega hay que agregar textos, **precio y URL** a los componentes (en las propiedades).

---

### Links de la clase

* https://github.com/disenoUDP/mi-primer-esquematico
* https://misaaaaaa.github.io/imagen-talvez/magos.html
* https://afagaleria.cl/artistas/delight-lab/?v=5bc574a47246
* https://github.com/misaaaaaa/1byteDreamer
* https://github.com/piruetasxyz/plexo
* https://dl.acm.org/doi/pdf/10.1145/2460625.2460711

---

## 2. Encargos

Esta clase no hubo encargo.

---

## 3. Lectura

**Texto:** *Anarchy* — John Cage. Páginas 32 a 39.

### Qué entendí

* Las páginas 32 y 33 repiten una y otra vez la misma idea: la naturaleza humana es simple y todos compartimos una sola mente, así que cambiar las cosas de raíz es sencillo, porque basta con cambiar esa mente.
* Más adelante (págs. 34 a 38) habla de los gobiernos, los soldados y el dinero, y de cómo las redes eléctricas globales y la tecnología podrían hacer la vida más honesta y liberarnos de ellos.
* La sección 8 (pág. 39) parte planteando el problema de hoy: una libertad puramente formal no es libertad de verdad. Termina con la idea de la libertad de cada uno a través de la libertad de todos.
* Nota: como el texto está tan fragmentado, el resumen y la reflexión los armé con ayuda de IA, y el resumen es una lectura mía, no una certeza.

### Cita interesante

> "Liberty of each through the liberty of all" (p. 39)

### Reflexión/definición personal

Esta frase me quedó dando vueltas porque dice que mi libertad no sirve de mucho si la del resto no existe. Hoy se habla de la libertad como algo individual, cada uno por su lado y salvándose solo. Pero una libertad de verdad necesita condiciones para todos: poder educarte, tener salud, un trabajo digno y decidir sobre tu propia vida. Si a mí me va bien porque a otros les va mal, no es libertad, es privilegio. Por eso leo la idea de Cage hacia lo colectivo: nadie es libre del todo hasta que lo somos todos. Y lo conecto con lo que hacemos en el taller, porque las máquinas y las redes también se pueden usar para compartir y no solo para controlar.
