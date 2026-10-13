# sesion-08a

2026.10.06

## apuntes sesión

No asistí a esta clase, así que los apuntes son basados en los repos de mis compañeres jiji

---

### Clase repaso

Las clases se componen en atributos y métodos, allows subclases

```cpp
class Algo {
    
    // atributos
    bool esAlgo;
    int cuantoAlgo;

    // metodos
    void algo();

}
```

### Clase LED

- Dos estados de encendido para la luz: si o no

- Brightness ranges from 0 to 255

- Se define según el umbral (&uarr; on / &darr; off)

- Can parpadear, pero depende del tiempo

Eg. `LuzNavidad = Lucecita[100];`

- Colores RGB (rojo, verde, azul)

- Botón &harr; Lucecita &harr; Usuario &harr; Botón (cíclico)

[Pinout LED RGB](./imagenes/rgbled-pinout.jpg)

```cpp
class EspantaCuco {

int precio;
Lucecita espantadora; // instancia
Sensor luminico;

} 
```

```cpp
class Helado {

int precio;
cremosidad;
vegano;

}
```

---

- OOP &rarr; **O**bject-**O**riented **P**rogramming

- `.h` &rarr; son declaraciones (dice qué hace)

- `.cpp` &rarr; son definiciones (cómo lo hace lo que dice hacer ¿¿¿)

## encargos

encargo-08a:

1. tomar muchas fotos, mínimo 3 por cada uno de los 3 elementos que estudiamos hoy: perillas, botones, y luces. subir las fotos a su README como respuesta a este encargo, y describirlas textualmente, para con esa info complejizar nuestras clases programadas este viernes.

![Perilla 1](./imagenes/perilla1.jpg)

![Perilla 2](./imagenes/perilla1.jpg)

![Perilla 3](./imagenes/perilla1.jpg)

![Botón 1](./imagenes/boton1.jpg)

![Botón 2](./imagenes/boton2.jpg)

![Botón 3](./imagenes/boton3.jpg)

![Luz 1](./imagenes/luces1.jpg)

![Luz 2](./imagenes/luces2.jpg)

![Luz 3](./imagenes/luces3.jpg)

2. partir del ejemplo de hoy, que está subido en codigos/ de hoy, y hacer que las luces parpadeen. para eso, definir parpadeo de forma paramétrica.

## lectura
