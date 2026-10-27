# sesion-11a

2026.10.27

## apuntes sesión

Realicé la primera versión del diagrama de flujo del proyecto. Primera vez que hago uno en markdown lol así que aprendí un nivel muy básico del syntax de `mermaid`

```mermaid
%%{ init : { "theme" : "default", "flowchart" : { "curve" : "linear" }}}%%
%%                                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

flowchart TD

%%==============================================================================

    A(<b>Inicio / Reiniciar</b>\n Pantalla vacía, estado MOVER)--->B(<b>Leer perillas y botones</b>\nUna vez por iteración);
    B-->C{¿Borrar?};
    C--->|No|D{¿Trazo pulsado?};
    C-->|Si|E(<b>Borrar</b>\nLimpiar estado = MOVER);
    D-->|No|F(<b>Calcular posición</b>\nMapear, limitar, filtrar ruido);
    D--->|Si|G(<b>Alternar MOVER / DIBUJAR</b>\nSi activa: anterior = cursor);
    E-->F;
    G-->F;
    F-->H{¿Modo dibujar?};
    H--->|Si|I(<b>Dibujar línea</b>\nUne anterior con actual);
    H--->|No|J(<b>Actualizar pantalla</b>\nanterior = actual);
    H-->|repite|A;
```

---

Esta primera versión era un diagrama más generalizado, así que ahora voy a diferenciar entre el diagrama de flujo del usuario, y el flujo del programa

### Diagrama de flujo del usuario

```mermaid
%%{ init : { "theme" : "default", "flowchart" : { "curve" : "linear" }}}%%
%%                                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

flowchart TD

%%==============================================================================

A(<b>Iniciar</b>\nPantalla vacía, TRAZO desactivado)-->B(<b>Observar estado MOVER</b>\nEl indicador muestra MOVER);
B-->C(<b>Posicionar cursor</b>\nGirar perillas, sin marcar);
C-->D{¿Dibujar?};
D-->|Si|E(<b>Pulsar TRAZO</b>\n Activa DIBUJAR);
E-->F(<b>Mover perillas</b>\nSe dibuja una línea contínua);
F-->G{¿Qué sigue?};
G-->H(<b>Desplazarse sin marca</b>\nPulsar TRAZO: vuelve a MOVER);
D--->|No|C;
H-->C;
G--->|Continuar|F;
G-->I(<b>Borrar</b>\nLimpia y vuelve a MOVER);
I-->B;
```

### Diagrama de flujo del programa

```mermaid
%%{ init : { "theme" : "default", "flowchart" : { "curve" : "linear" }}}%%
%%                                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

flowchart TD

%%==============================================================================


```

## lectura
