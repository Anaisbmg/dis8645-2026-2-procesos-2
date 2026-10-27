# proyecto-02

## Nombre del proyecto

**Integrantes:** 
- Magdalena Balart [_(magdalenabalart)_](https://github.com/disenoUDP/dis8645-2026-2-procesos-2/tree/main/02-magdalenabalart)
- Catalina Oyanedel [_(catalinaoyanedel-01)_](https://github.com/disenoUDP/dis8645-2026-2-procesos-2/tree/main/17-catalinaoyanedel-01)
- Yaira Ruiz [_(yairaruiz)_](https://github.com/disenoUDP/dis8645-2026-2-procesos-2/tree/main/26-yairaruiz)
- Marcela Zuñiga [_(marcezm)_](https://github.com/disenoUDP/dis8645-2026-2-procesos-2/tree/main/32-marcezm)


## Descripción general
El proyecto consiste en una máquina que tiene como fin ser un acompañamiento emocional, permitiendo explorar distintas formas de interactuar.

La máquina cuenta con tres estados de la pantalla principales:

- Modo 01 – Expresiones: muestra un rostro cuya expresión emocional puede modificarse.
- Modo 02 – Mensajes: presenta un mensaje variable asociado a la emoción seleccionada anteriormente y se pueden explorar más.
- Modo 03 – Minijuego: presenta un juego en el que un personaje debe saltar obstáculos. Su nivel de dificultad cambia dependiendo de la emoción seleccionada.

### Referentes
Nuestra principal inspiración son los computadores de juguete de los años 2000, los cuales imitaban la apariencia de computadores convencionales, pero adaptaban sus funciones a una interacción más simple y accesible. Estos juguetes ofrecían experiencias de aprendizaje y entretenimiento mediante actividades predeterminadas, personajes digitales y juegos sencillos, utilizando pantallas simples y botones para ofrecer estas experiencias.

Elegimos como principal referente un Digital Desktop PC de la marca KB Learning Toys.

![referente](./imagenes/referente.png)


### Decisiones
A partir de este referente, destacamos sus características como pantallas LCD, los botones físicos, colores vívidos, el teclado, los gráficos de baja resolución y que cuenta con estos tres modos (word games, math games y fun games). Decidimos mantener la estructura del monitor, ocupar el recurso del teclado para tener nuestros botones y perillas separadas de la pantalla, para proponer una experiencia similar a la de este tipo de computador, y tener 3 modos de "juego", reinterpretándolo con nuestro objetivo.

#### Boceto:
![boceto](./imagenes/boceto.png)


#### Materialidad e interfaz
Planeamos realizar la carcasa en impresión 3d, para mantenernos fiel a las formas y materiales de nuestro referente. La interfaz está en desarrollo.

---

## Funcionamiento del sistema

### Diagramas de flujos

#### Usuario:
```mermaid
flowchart TB
   Start(["Presionar botón 01"]) --> PowerOn["Máquina encendida"]
   PowerOn --> Screen1["Pantalla 1: Rostro con expresión"]
   Screen1 --> Pot01{"Potenciómetro 01:<br/>Seleccionar emoción"}

   Pot01 -->|Felicidad| Happy["Felicidad"]
   Pot01 -->|Tristeza| Sad["Tristeza"]
   Pot01 -->|Enojo| Angry["Enojo"]
   Pot01 -->|Calma| Calm["Calma"]

   Happy --> StoreEmotion["Guardar emoción seleccionada"]
   Sad --> StoreEmotion
   Angry --> StoreEmotion
   Calm --> StoreEmotion

   StoreEmotion --> Pot02{"Potenciómetro 02:<br/>Navegar por las pantallas"}

   Pot02 -->|Estado 1| Screen1
   Pot02 -->|Estado 2| Screen2["Pantalla 2: Mensaje<br/>según emoción"]
   Pot02 -->|Estado 3| Screen3["Pantalla 3: Minijuego"]

   Screen2 --> Pot02

   Screen3 --> DifficultyCheck{"¿Qué emoción<br/>está almacenada?"}

   DifficultyCheck -->|Calma| CalmSpeed["Velocidad muy lenta<br/>Muy pocos obstáculos"]
   DifficultyCheck -->|Tristeza| SadSpeed["Velocidad lenta<br/>Pocos obstáculos"]
   DifficultyCheck -->|Felicidad| HappySpeed["Velocidad media<br/>Obstáculos moderados"]
   DifficultyCheck -->|Enojo| AngrySpeed["Velocidad muy rápida<br/>Obstáculos muy frecuentes"]

   CalmSpeed --> GameStart["Iniciar minijuego"]
   SadSpeed --> GameStart
   HappySpeed --> GameStart
   AngrySpeed --> GameStart

   GameStart --> Obstacles["Personaje avanza<br/>y aparecen obstáculos"]
   Obstacles --> Jump["Botón 02: Saltar"]
   Jump --> Collision{"¿Chocó con<br/>un obstáculo?"}

   Collision -->|No| Obstacles
   Collision -->|Sí| GameOver["Fin de la partida"]

   GameOver --> Replay{"¿Qué desea hacer?"}
   Replay -->|Jugar otra vez| GameStart
   Replay -->|Volver al recorrido| Pot02

   PowerOn:::action
   Screen1:::screen
   Pot01:::decision
   Happy:::emotion
   Sad:::emotion
   Angry:::emotion
   Calm:::emotion
   StoreEmotion:::action
   Pot02:::decision
   Screen2:::screen
   Screen3:::screen
   DifficultyCheck:::decision
   CalmSpeed:::game
   SadSpeed:::game
   HappySpeed:::game
   AngrySpeed:::game
   GameStart:::action
   Obstacles:::game
   Jump:::game
   Collision:::decision
   GameOver:::game
   Replay:::decision

   classDef screen fill:#eef2ff,stroke:#818cf8
   classDef emotion fill:#f0fdf4,stroke:#4ade80
   classDef action fill:#fdf4ff,stroke:#e879f9
   classDef game fill:#fff7ed,stroke:#fb923c
   classDef decision fill:#ecfeff,stroke:#22d3ee
```

### Esquemático

![Esquemático](esquematico.png)

#### BOM: Lista de componentes

| Componente | Pin | Nota |
|------------|-----|------|
| Rasberry Pi Pico 2W |  | |
|  | |  |

## Estructura del código

```
codigo/
├── main.cpp
    └── Boton.h / Boton.cpp
    └── Perilla.h / Perrilla.cpp
    └── Emociones.h / Emociones.cpp
    └── Mensajes.h / Emociones.cpp
    └── Juego.h / Juego.cpp
```

### Clases escritas por nosotras

#### `[NombreClase]`
- **Qué hace:** 
- **Atributos:** 
- **Métodos:** 
- **Se relaciona con:** 

```cpp
class NombreClase {
  private:
    bool encendido;
  public:
    void encender();   // qué hace, en una línea
};
```

#### Prompts usados:
para qué se usó cada uno y qué se hizo con la respuesta.

### Clases de terceros
Hechas por grupo 04

#### `[NombreClase]`
- **Qué hace:** 
- **Atributos:** 
- **Métodos:** 
- **Se relaciona con:** 


# Resultados
fotos, videos

### Aprendizajes
conclusiones, reflexiones del proceso

### Reparto del trabajo
| Integrante | Tareas |
|------------|--------|
| Nombre 1 | Código |
| Nombre 2 | Circuito |
| Nombre 3 | Interfaz |

### Bibliografía:
fuentes consultadas.


