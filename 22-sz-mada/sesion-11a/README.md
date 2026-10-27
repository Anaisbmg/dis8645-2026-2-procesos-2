# sesion-11a

2026.10.27

## apuntes sesión

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

## lectura
