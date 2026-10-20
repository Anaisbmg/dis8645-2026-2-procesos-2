# sesion-09a

## apuntes sesión

### 1. ¿Qué es KiCad?

**KiCad** es un software de diseño electrónico que permite crear esquemas de circuitos y diseñar placas de circuito impreso (**PCB**, por sus siglas en inglés).

En clase comenzamos a utilizarlo siguiendo un proceso general de diseño:

1. **Realizar el esquema electrónico (diseño esquemático):** definir los componentes y sus conexiones, es decir, la topología del circuito. Esto se puede relacionar con la teoría de grafos, ya que se representan elementos conectados entre sí.
   - **Objetivo principal de la clase:** comprender y dominar las conexiones entre los componentes.
   - Por convención, muchos esquemas se organizan para leerse de **izquierda a derecha**, aunque esto depende del circuito.
2. **Diseñar y visualizar el soporte físico:** distribuir los componentes y sus conexiones en la placa (PCB).
3. **Visualizar el diseño físico en 3D:** revisar el aspecto de la placa y la disposición de los componentes.

> **Nota:** KiCad permite diseñar circuitos que pueden formar parte de controladores o módulos electrónicos, por ejemplo, dispositivos asociados a pantallas OLED de Adafruit.

### 2. Agregar componentes al esquema

En el editor de esquemas, utilizamos la herramienta **«Colocar símbolos»** para buscar e insertar los componentes electrónicos. La biblioteca de símbolos representa las conexiones eléctricas; la apariencia física del componente se gestiona mediante su huella (*footprint*) y su modelo 3D, cuando están disponibles.

### Componentes utilizados en clase

| Componente | Cómo buscarlo en KiCad | Observaciones |
|---|---|---|
| Raspberry Pi | Buscar el modelo exacto en la biblioteca de símbolos | Revisar la correspondencia de pines del modelo empleado. |
| Potenciómetro | `Device:R_Potentiometer` | En el ejercicio se utilizó uno de **100 kΩ** (`B100K`). |
| Tierra | `GND` (biblioteca `power`) | Referencia de tierra del circuito. |
| Alimentación de 3,3 V | `+3V3` (biblioteca `power`) | Símbolo de alimentación. |
| Pulsador | `SW_Push` | Interruptor momentáneo. |
| Resistencia | `Device:R` | El valor se define según su función. |
| LED | Buscar `LED` | Verificar su orientación y polaridad. |

### Editar componentes y valores

- Para cambiar el valor de un componente, por ejemplo una resistencia, hacer **doble clic** sobre su símbolo y modificar el campo correspondiente.
- Para orientar los componentes, se pueden utilizar los atajos:
  - **`R`**: girar el símbolo.
  - **`X`**: reflejar el símbolo horizontalmente.
  - **`Y`**: reflejar el símbolo verticalmente.

**Método de trabajo:** primero insertar los componentes que se usarán; después, organizarlos y realizar sus conexiones.

### 3. Conectar los componentes

Para dibujar un cable, iniciar la conexión desde el **extremo del pin** de un componente y llevarla hasta el pin o nodo correspondiente. En KiCad se utiliza la herramienta de cableado para realizar estas uniones.

### Mover componentes

- **`G` (arrastrar):** mover un componente manteniendo sus conexiones, cuando sea posible.
- **`M` (mover):** desplazar el componente sin arrastrar de la misma manera los cables conectados.

### Conexiones realizadas en clase

#### 3.1. Alimentación de la Raspberry Pi

1. Conectar el pin **GND (pin físico 3, según lo anotado en clase)** al símbolo `GND`.
2. Conectar la alimentación **`+3V3`** al pin correspondiente de la Raspberry Pi.

> **Importante:** antes de replicar las conexiones en hardware, verificar el **modelo exacto de la placa y su pinout**. La numeración de los pines puede variar según el dispositivo. La referencia «GND (3)» se conserva de los apuntes originales y debe comprobarse en el esquema utilizado.

#### 3.2. Potenciómetro

El potenciómetro usado en el ejercicio tiene un valor de **100 kΩ** (`B100K`). Las conexiones anotadas son:

| Terminal del potenciómetro | Conexión |
|---|---|
| **1** | `+3V3` |
| **2** (cursor) | `GP26` de la Raspberry Pi (**pin físico 31**, según los apuntes) |
| **3** | `GND` |

De este modo, el terminal central entrega una señal variable al pin de entrada.

#### 3.3. LED y resistencia

El circuito del LED se conectó siguiendo esta secuencia:

```text
Raspberry Pi (GP7 / pin 10) ── LED ── R (220 Ω) ── GND
```

La resistencia de **220 Ω** se coloca en serie con el LED para limitar la corriente. Hay que respetar la polaridad del LED.

#### 3.4. Pulsador y resistencia

Las conexiones anotadas para el pulsador son:

```text
                   GP10 (pin 14)
                         │
+3V3 ─── Pulsador ────────┴──── R (100 kΩ) ─── GND
```

Este esquema corresponde a una entrada con resistencia **pull-down**: sin pulsar, la resistencia mantiene la señal cerca de `GND`; al pulsar, se conecta a `+3V3`.

> **Referencia utilizada:** en general, observamos el circuito armado en **Wokwi** y después lo reproducimos en el esquema de KiCad.

### 4. Crear y utilizar etiquetas de red

KiCad permite crear **etiquetas de red** (*net labels*) para identificar conexiones eléctricas y conectar partes del circuito sin tener que dibujar cables largos entre ellas.

### Ejemplo: etiqueta `perilla`

1. Crear el circuito del potenciómetro: terminal **1** a `+3V3`, terminal **3** a `GND` y terminal **2** como señal de salida.
2. Utilizar la herramienta **«Colocar etiqueta»** y crear una etiqueta llamada **`perilla`**.
3. Colocar la etiqueta `perilla` en el cable que sale del **terminal 2** del potenciómetro.
4. Colocar otra etiqueta con el **mismo nombre** en la conexión de entrada **GP26** de la Raspberry Pi.
5. Reemplazar el cable largo entre ambos puntos por esas etiquetas, si corresponde.

**Resultado:** las conexiones con el mismo nombre de red quedan vinculadas eléctricamente dentro del ámbito correspondiente del esquema, aunque no haya un cable visible entre ellas.

Este mismo procedimiento puede aplicarse a otras señales para **ordenar el esquema y separar visualmente los subcircuitos**.

> Las etiquetas no agrupan automáticamente todo un subcircuito: identifican la **red eléctrica** a la que se conectan.

### 5. Indicar pines sin conexión

Si un terminal de un componente no se utiliza, es posible marcarlo con la herramienta **«Colocar indicadores sin conexión»** (*No Connect*).

Esto permite dejar claro que ese pin se mantiene desconectado **de manera intencional** y ayuda a interpretar las advertencias de la comprobación de reglas eléctricas (**ERC**).

### 6. Crear símbolos personalizados

KiCad ofrece la posibilidad de diseñar símbolos que no estén disponibles en sus bibliotecas, por ejemplo, el símbolo de una pantalla utilizada en clase.

Para hacerlo:

1. Ir a **Herramientas** en la barra superior.
2. Abrir el **Editor de símbolos**.
3. Crear un símbolo nuevo y definir sus pines y su representación gráfica.

> **Importante:** crear un símbolo esquemático no equivale a crear la huella física del componente. Para diseñar una PCB, también se necesita una huella (*footprint*) adecuada.

### 7. Recomendaciones y recordatorios

- **Abrir el proyecto desde su archivo `.kicad_pro`** para mantener vinculados los archivos del diseño. En los apuntes originales aparece como «`.pro`»; en las versiones actuales de KiCad, la extensión habitual es `.kicad_pro`.
- Al agregar módulos o componentes, **identificar el modelo exacto**. Dos dispositivos que cumplen la misma función pueden tener distinta distribución física y eléctrica de pines, como ocurre con algunos modelos de pantallas.
- **Verificar la numeración de pines** antes de conectar componentes reales, especialmente en la Raspberry Pi.
- Organizar el esquema con etiquetas para evitar cruces y recorridos de cable innecesarios.
- Antes de pasar al diseño físico, revisar las conexiones y, cuando corresponda, ejecutar la **comprobación de reglas eléctricas (ERC)**.

---

## Resumen rápido de atajos

| Atajo | Función |
|---|---|
| `R` | Girar símbolo. |
| `X` | Reflejar horizontalmente. |
| `Y` | Reflejar verticalmente. |
| `G` | Arrastrar componente con sus conexiones. |
| `M` | Mover componente. |



## encargos

## lectura
