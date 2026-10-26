Hola, grupo 06 y a todes quienes ven este texto. Estas son las especificaciones de cómo queremos que sea la biblioteca y el desarrollo de nuestros botones.
  
// ============================================================
// BOTÓN 1: moverse por los niveles y elegir uno
// (solo se usa en el menú de niveles, la acción de navegar
// y seleccionar el nivel con el que la persona va a jugar)
// ============================================================
// Este botón va a tener estados:
// noPresionado
// estaSiendoPresionado
// soltado
//
// Atributos
//
// Qué necesita saber este botón:
//  - En qué pin está conectado de la raspberry.
//  - Si en este momento está presionado o noPresionado.
//  - Soltado.
//  - Cuánto tiempo esperar para decidir si fue una o dos pulsaciones:
//    0,6 segundos desde la primera pulsación.
//    (Debe quedar como una constante fácil de cambiar en el .h,
//    por si al probar con personas reales hay que ajustarla.)
//  - Cuántas veces lo han presionado en este intento (0, 1 o 2).
//  - Cuándo fue la última vez que lo presionaron.

// Qué hace:
//  Cuando la persona presiona el botón por primera vez, el botón pasa
//  de noPresionado a estaSiendoPresionado. Cuando ella lo suelta,
//  pasa a soltado, cuenta UNA pulsación, anota la hora y vuelve
//  a noPresionado. En ese momento el botón todavía no avisa nada:
//  empieza a esperar 0,6 segundos para ver si viene una segunda
//  pulsación.
//
//  Si dentro de esos 0,6 segundos la persona lo presiona otra vez
//  (y lo suelta), el botón avisa: "fueron DOS pulsaciones". Eso
//  significa que ella quiere SELECCIONAR el nivel en el que está.
//
//  Si pasan los 0,6 segundos y no hubo segunda pulsación, el botón
//  avisa: "fue UNA pulsación". Eso significa que ella quiere
//  CAMBIAR al siguiente nivel.
//
//  Para que cuente una nueva pulsación, el botón primero debe soltarse
//  y volver a ser presionado. Si la persona lo deja presionado, cuenta
//  como una sola pulsación y no se repite sola.
//
//  Después de avisar, el botón se reinicia y queda listo para empezar
//  de nuevo. Si la persona presiona tres veces o más, se cuentan solo
//  las dos primeras y lo demás se ignora.

// Cómo debe reaccionar el programa principal:
//  - Si el aviso es UNA pulsación: pasar al siguiente nivel
//    (del 1 al 2, del 2 al 3, y del 3 vuelve al 1).
//  - Si el aviso es DOS pulsaciones: confirmar el nivel y empezar el juego.
//  - Mientras se juega, este botón no se consulta, no hace nada.
//
// Nota importante:
//  Como la máquina espera 0,6 segundos para estar segura de que no viene
//  una segunda pulsación, el cambio de nivel tarda ese tiempo en notarse.
//  Para que la persona no sienta que el botón "no responde", hacer 
//  que esta acción de un feedback inmediata al primer clic
//  por medio de un parpadeo corto de una LED o un sonido, aunque el
//  cambio de nivel se confirme después.


// ============================================================
// BOTÓN 2: atrapar la luz
// (solo se usa durante el juego, la acción de jugar y atrapar
// la luz del LED)
// ============================================================
// Este botón va a tener estados:
// noPresionado
// estaSiendoPresionado
// soltado
//
// Atributos
//
// Qué necesita saber este botón:
//  - En qué pin está conectado de la raspberry.
//  - Si en este momento está presionado o noPresionado.
//  - Soltado.
//  No tiene límite de tiempo ni tiempo de descanso, a propósito.

// Qué hace:
//  Cada vez que la persona presiona el botón, el botón avisa de
//  inmediato: "intentó atrapar". Sin esperas y sin límite de
//  pulsaciones por segundo.
//
//  Esto es importante porque en los niveles rápidos, o cuando la persona
//  sube la velocidad con la perilla 1, las luces bajan muy rápido
//  y ella necesita presionar muy rápido también.
//  El botón tiene que poder seguirle el ritmo.
//
//  Para que cuente una nueva pulsación, el botón primero debe soltarse
//  y volver a ser presionado. Si la persona lo deja presionado, cuenta
//  como un solo intento y no se repite solo.
//  No importa cuánto tiempo lo mantenga presionado: el botón no se
//  bloquea ni da error por eso.

// Cómo debe reaccionar el programa principal:
//  El botón NO decide si la luz fue atrapada. Solo avisa que la persona
//  presionó. Quien decide es el programa principal, y revisa dos cosas:
//    1. ¿Había una luz en la zona de captura?
//    2. ¿El LED de la jugadora estaba en el mismo camino que esa luz?
//       (El LED siempre está en uno de los 4 caminos, según
//       dónde esté la perilla 2.)
//
//  Si las dos respuestas son sí, la luz se atrapa y el juego sigue.
//  Si alguna respuesta es no, la jugadora pierde y regresa
//  al menú de niveles.
//
//  Durante el menú de niveles, este botón no hace nada.
