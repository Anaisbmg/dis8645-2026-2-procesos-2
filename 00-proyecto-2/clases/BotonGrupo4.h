 // Nuestro proyecto se basara en el texto multitap que tenian los telefonos como los Nokia,
 // los cuales cada nmeros contiene 3 letras que debes presionar para que estos aparecieran 
 // en la pantalla, tambien en los joystick de la PS1, que permitian digitar textos cortos 
 // para anadir nombres de usuario, entre otras cosas.

 // Bajo esta idea, queremos generar una maquina en donde en una pantalla se puedan digitar 
 // caracteres, en donde todos estos tienen variaciones que pueden ser seleccionadas presionando
 //  un boton 2 veces, lo que hace que el caracter impreso sea en mayuscula. Ademas, queremos 
 // anadir como opcion caracteres especiales, tab, enter, etc.

 // Funciona a traves de un selector de caracteres (perilla), que nos permite escoger las 
 // letras para formar palabras o no y finalmente seleccionarlas con un boton que puede ser 
 // presionado 1 o 2 veces.

 // Tambien podemos editar el texto que imprimimos en una segunda pantalla con una segunda 
 // perilla que puede recorrer el texto para anadir un caracter, borrarlo, o borrar todo lo 
 // digitado si se mantiene presionado.

 // Definición de atributos

 // PANTALLA 1 

 // Pantalla 1: imprime la información que fue previamente seleccionada en la pantalla 1, 
 // la cual se puede editar con la perilla 2 y el botón 2.

 // Perilla 1: debe recorrer el texto caracter por caracter de ida y/o de vuelta, permitiéndonos
 // editarlo en cualquier parte del texto (con botones).

 // Botón 1: dependiendo de la cantidad de pulsaciones (solo una pulsación) en la primera 
 // pantalla borra sólo un carácter, o (dos pulsaciones) se mantiene pulsado en la segunda pantalla

 // PANTALLA 2

 // Pantalla 2: proyecta los caracteres: (a, b, c, d, e, f, g, h, i, j,k, l, m, n, o, p, q, r, s, 
 // t, u, v, w, x, y, z, tab, enter) y en ella se recorren para seleccionarlos.

 // Perilla 2: debe recorrer los caracteres uno a uno para así poder seleccionar alguno, que el 
 // recorrido sea lento y que no se vaya todo de golpe de un extremo al otro. 

 // Botón 2: selecciona el carácter que se selecciona con la perilla 1, si se presiona una vez, 
 // la letra se imprime en minúscula, y si se presiona 2 veces se imprime en mayúscula.

