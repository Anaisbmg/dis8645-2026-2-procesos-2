# sesion-10a

## apuntes sesión

# TRAZO

No nos anotamos para corregir en esta sesión, pero aun así nos reunimos con mi grupito 07 y concretamos más o menos nuestra idea!!!

## Idea del proyecto

La idea es hacer una **máquina de dibujo digital que se controle con dos perillas y dos botones**.

En la pantalla aparece un punto que podemos mover de izquierda a derecha y de arriba abajo. Después, con un botón, decidimos si queremos que ese movimiento deje una línea o si solamente queremos cambiar el punto de lugar.

O sea, podemos movernos por la pantalla **sin dibujar** y activar el trazo cuando lleguemos al lugar donde queremos empezar.

Le pusimos **TRAZO** porque la propuesta gira justamente en torno a eso: mover un punto y decidir cuándo ese movimiento se convierte en dibujo.

## Referente

Nuestro referente es **MacPaint de 1984**.

Tomamos principalmente:

- El dibujo con píxeles.
- El uso del blanco y negro.
- La idea de tener herramientas simples.
- Que podamos ver inmediatamente en la pantalla lo que estamos haciendo.

Pero en nuestro caso queremos llevar esa experiencia a **controles físicos**.

Una perilla mueve el punto horizontalmente y la otra lo mueve verticalmente.

No queremos reproducir todas las herramientas de MacPaint porque para esta primera versión queremos concentrarnos en dos acciones principales:

- Activar o desactivar el trazo.
- Borrar.

[Referencia: MacPaint y QuickDraw — Computer History Museum](https://computerhistory.org/blog/macpaint-and-quickdraw-source-code/)

# ¿Qué queremos que pase?

La persona puede empezar haciendo líneas rectas y después ir probando qué pasa cuando mueve las dos perillas al mismo tiempo.

Una mano controla el movimiento horizontal y la otra el vertical.

Entonces hay que ir **coordinando los dos movimientos** para poder construir:

- Líneas horizontales.
- Líneas verticales.
- Diagonales.
- Curvas.
- Figuras.

La idea es aprender usándolo, porque probablemente al principio cueste un poco hacer exactamente la forma que una tiene en la cabeza jiji.

No existe una figura que tengamos que copiar.

Tampoco hay:

- Puntaje.
- Tiempo límite.
- Una forma correcta de dibujar.

Podemos dibujar libremente y dejar el resultado en la pantalla hasta que decidamos borrarlo.

# ¿Qué hace cada cosa?

| **Elemento** | **Función** |
| --- | --- |
| Perilla horizontal | Controla la posición del punto de izquierda a derecha. |
| Perilla vertical | Controla la posición del punto de arriba abajo. |
| Botón de trazo | Activa o desactiva el dibujo. |
| Botón de borrar | Borra todo el dibujo y deja el trazo desactivado. |
| Pantalla | Muestra el punto, las líneas y si estamos moviendo o dibujando. |

# Las perillas

Las perillas controlan la **posición del punto**.

Esto significa que cada posición de la perilla corresponde a un lugar de la pantalla.

Por ejemplo:

Si giro una perilla hasta la mitad y la dejo ahí, el punto llega a esa posición y **se queda ahí también**.

No sigue avanzando solo.

Esto es importante porque la perilla no controla una velocidad, sino directamente una posición.

## Movimiento horizontal

Una perilla controla la coordenada horizontal, que sería la posición en el eje **X**.

- En el mínimo de su recorrido, el punto queda en el borde izquierdo.
- En el máximo, queda en el borde derecho.
- Aproximadamente a la mitad, queda al centro horizontal del área de dibujo.

Entonces podemos pensarlo más o menos así:

```text
mínimo          mitad           máximo
  ↓               ↓                ↓

izquierda ------- centro ------- derecha
```

## Movimiento vertical

La otra perilla controla la coordenada vertical, que sería la posición en el eje **Y**.

- En el mínimo de su recorrido, el punto queda arriba.
- En el máximo, queda abajo.
- Aproximadamente a la mitad, queda al centro vertical del área de dibujo.

Entonces, si **las dos perillas están a la mitad**, el punto debería quedar cerca del centro de la pantalla.

Si movemos solamente una perilla, podemos construir una línea horizontal o vertical.

Si movemos las dos al mismo tiempo, podemos ir formando diagonales o curvas dependiendo de cómo coordinemos nuestros movimientos.

## Los límites

El punto tampoco puede salir del área de dibujo ni aparecer mágicamente al otro lado de la pantalla jajaja.

Cuando llega al borde, **ese es su límite**.

Entonces tenemos que hacer que los valores de las perillas correspondan solamente al espacio que realmente tenemos disponible para dibujar.

# Mover y dibujar

La máquina tiene dos estados principales:

```text
MOVER
DIBUJAR
```

## `MOVER`

En este estado el punto cambia de posición, pero **no deja líneas nuevas**.

Lo que ya dibujamos se mantiene en la pantalla.

Solamente estamos cambiando el lugar desde donde queremos seguir.

Es como **levantar el lápiz del papel**, moverlo a otra parte y después volver a apoyarlo.

## `DIBUJAR`

En este estado el punto cambia de posición y **va dejando una línea**.

Acá sería como volver a apoyar el lápiz sobre el papel y empezar a dibujar desde donde estamos.

| **Estado** | **Qué pasa cuando movemos las perillas** |
| --- | --- |
| `MOVER` | El punto se desplaza sin dejar un trazo permanente. |
| `DIBUJAR` | El punto se desplaza dejando una línea. |

# Botón de trazo

El botón de trazo cambia entre los dos estados.

Si estamos en:

```text
MOVER
```

y lo presionamos, pasamos a:

```text
DIBUJAR
```

Si lo volvemos a presionar, regresamos a:

```text
MOVER
```

No tenemos que mantener el botón apretado.

**Una pulsación cambia el estado y ese estado se mantiene hasta que volvamos a presionarlo.**

Esto es importante porque así tenemos las dos manos disponibles para mover las perillas.

Porque si tuviéramos que dejar un botón apretado mientras además controlamos dos perillas sería medio imposible JAJJA.

## Ojo con cada pulsación

Algo importante es que **cada pulsación produzca solamente un cambio de estado**.

Si mantengo el botón presionado, no debería empezar a cambiar entre `MOVER` y `DIBUJAR` veinte veces seguidas.

Tiene que entender:

```text
una pulsación
      ↓
un cambio
```

# ¿Dónde comienza cada trazo?

Cada vez que activamos el dibujo, el trazo tiene que comenzar desde **la posición actual del punto**.

Por ejemplo:

1. Dibujamos algo en la izquierda.
2. Desactivamos el trazo.
3. Nos movemos hacia la derecha.
4. Volvemos a activar el trazo.

El nuevo dibujo tiene que comenzar **a la derecha**, donde está ahora el punto.

No debería aparecer una línea atravesando toda la pantalla para conectar automáticamente el dibujo anterior con el nuevo.

Eso sería medio desastre jajaja.

# ¿Cómo se forma el dibujo?

Mientras estamos en `DIBUJAR`, el programa une:

```text
posición anterior del punto
            +
posición nueva del punto
```

Así buscamos que aparezca una **línea continua**.

Si solamente mostráramos cada posición nueva por separado, al mover las perillas rápido podrían aparecer muchos puntos separados.

La idea es que se unan para que realmente se vea como un trazo.

## Primera versión del dibujo

Para esta primera versión queremos trabajar con:

- Un solo grosor de línea.
- Trazos blancos sobre fondo negro, si usamos una pantalla OLED monocromática.
- Líneas que se van acumulando.
- Trazos que pueden pasar por encima de otros sin borrarlos.

O sea, si dibujo un círculo y después hago otra figura, **el círculo sigue ahí**.

Y si vuelvo a pasar por encima de una línea, eso tampoco funciona como goma.

# El punto y el dibujo

El punto que muestra dónde estamos tiene que seguir siendo visible aunque el trazo esté desactivado.

Pero ojo:

**que se vea no significa que tenga que dejar una marca.**

Tenemos que separar dos cosas:

```text
CURSOR → se mueve

DIBUJO → permanece
```

El cursor nos muestra dónde estamos.

Las líneas muestran lo que ya dibujamos.

La forma exacta del cursor todavía la tenemos que probar cuando tengamos definida la pantalla, porque tenemos que ver qué forma permite distinguirlo mejor del dibujo.

# Botón de borrar

El segundo botón sirve para **borrar todo el dibujo**.

Cuando lo presionamos:

1. Se eliminan todas las líneas.
2. La máquina vuelve al estado `MOVER`.

Esto permite que después podamos ubicarnos nuevamente antes de comenzar otro dibujo.

Para esta primera versión el borrado será **inmediato**.

No vamos a tener algo como:

```text
¿ESTÁS SEGURA DE QUE QUIERES BORRAR?
SÍ / NO
```

Nop jajaja.

Presionamos y se borra.

El botón tiene que estar claramente identificado como:

```text
BORRAR
```

## ¿Qué pasa con la posición del punto?

Borrar **no devuelve automáticamente el punto al centro**.

Esto pasa porque su posición depende directamente de las perillas.

Por ejemplo:

Si las perillas tienen el punto abajo a la derecha y presionamos `BORRAR`:

```text
dibujo → desaparece

estado → vuelve a MOVER

posición → sigue abajo a la derecha
```

Entonces lo que reiniciamos es:

- El dibujo.
- El estado del trazo.

Pero **no la posición de los controles**.

# ¿Cómo se divide la pantalla?

Queremos separar la pantalla en dos partes.

| **Zona** | **Contenido** |
| --- | --- |
| Franja de estado | Muestra `MOVER` o `DIBUJAR`. |
| Área de dibujo | Muestra el punto y las líneas que hacemos. |

Las perillas solamente pueden recorrer **el área de dibujo**.

La franja de estado queda fuera de ese espacio porque, si pudiéramos dibujar encima, terminaríamos tapando la información.

Todavía tenemos que confirmar el modelo y la resolución de la pantalla para saber exactamente cuánto espacio ocupa cada parte.

# ¿Qué pasa al iniciar?

Cuando comienza la simulación:

1. El área de dibujo está vacía.
2. La máquina parte en `MOVER`.
3. Se leen las posiciones de las dos perillas.
4. El punto aparece donde corresponde según esas posiciones.
5. Podemos moverlo y activar el trazo cuando queramos.

El punto **no tiene que comenzar siempre al centro**.

Su posición inicial depende de cómo estén ubicadas las perillas en ese momento.

En esta primera versión tampoco vamos a guardar los dibujos entre reinicios.

Si reiniciamos la simulación:

```text
dibujo anterior → adiós
```

y empezamos otra vez con el área vacía.

# Ejemplo de uso

Supongamos que queremos dibujar **dos figuras separadas**.

Primero, con el trazo desactivado, movemos el punto hasta donde queremos comenzar.

Después:

1. Presionamos el botón de trazo.
2. Pasamos a `DIBUJAR`.
3. Hacemos la primera figura usando las perillas.
4. Presionamos nuevamente el botón.
5. Volvemos a `MOVER`.
6. Llevamos el punto hacia otra parte de la pantalla sin dejar una línea.
7. Activamos nuevamente el trazo.
8. Dibujamos la segunda figura.

Si queremos empezar todo desde cero, presionamos `BORRAR`.

Entonces el recorrido general sería:

```text
Ubicar el punto
      ↓
Activar el trazo
      ↓
Dibujar
      ↓
Desactivar el trazo
      ↓
Moverse a otro lugar
      ↓
Volver a dibujar
```

O borrar todo y empezar de nuevo jijiji.

# Cosas por probar

Todavía tenemos varias cosas que necesitamos comprobar cuando empecemos a hacer las versiones reales del proyecto:

- [ ] Confirmar qué pantalla vamos a usar y su resolución.
- [ ] Definir cuánto espacio tendrá el área de dibujo y cuánto la franja de estado.
- [ ] Probar que todo el recorrido de las perillas corresponda correctamente con el área de dibujo.
- [ ] Revisar cómo se ve el cursor.
- [ ] Comprobar que en `MOVER` el punto no deje rastros.
- [ ] Comprobar que el cursor tampoco borre las líneas existentes.
- [ ] Revisar que una pulsación del botón cambie el estado solamente una vez.
- [ ] Comprobar que cuando activamos nuevamente el trazo no se conecte automáticamente con el dibujo anterior.
- [ ] Probar movimientos rápidos de las perillas para revisar que las líneas sigan viéndose continuas.
- [ ] Revisar que `BORRAR` realmente elimine todo el dibujo.
- [ ] Comprobar que después de borrar el estado vuelva a `MOVER`.
- [ ] Identificar bien cada control para que se entienda qué hace sin tener que explicarlo.

# Súper resumen

TRAZO funciona con **dos perillas + dos botones + una pantalla**.

```text
PERILLA X → movimiento horizontal

PERILLA Y → movimiento vertical

BOTÓN TRAZO → MOVER / DIBUJAR

BOTÓN BORRAR → limpia el dibujo

PANTALLA → muestra el cursor, el dibujo y el estado
```

Lo que más me interesa de la idea es que dibujar no depende solamente de mover una mano como cuando usamos un lápiz.

Acá tenemos que coordinar **dos movimientos separados**, uno para cada eje, y entender poco a poco cómo esos dos controles terminan construyendo una sola línea.

Siento que ahí está la parte más entretenida de TRAZO jiji.

## encargos

## lectura

En estas páginas entendí más que nada que los modelos matemáticos dejaron de usarse solo para estudiar y empezaron a aparecer en exposiciones, museos y hasta en el arte. Me llamó mucho la atención el ejemplo de Max Ernst, porque toma una figura matemática y la mezcla con la Venus de Milo, haciendo que algo que originalmente servía para explicar matemáticas termine teniendo otro significado completamente distinto. Siento que acá se empieza a mostrar súper claro cómo estas formas pueden salir de la ciencia y convertirse también en referencias visuales e inspiración para artistas y diseñadores.

“they moved from objects of research to objects of communication”- pág.78

“the catalogs were gateways to new modes of sight and knowledge.”- pág.80
