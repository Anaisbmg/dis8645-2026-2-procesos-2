#ifndef SAMPLE_H
#define SAMPLE_H

#include <stdint.h>

#define SAMPLE_RATE 24000

// Frecuencias de las notas en Hz
#define D4  293.66f
#define E4  329.63f
#define FS4 369.99f // F#
#define G4  392.00f
#define A4  440.00f
#define B4  493.88f
#define C5  523.25f
#define D5  587.33f
#define E5  659.25f
#define FS5 739.99f // F#
#define G5  783.99f
#define A5  880.00f

struct Note {
    float freq;
    uint32_t duration_ms;
};

// Duración estándar por nota (200ms da un tempo alegre tipo 8-bits)
#define T_NOTE 200 

const Note melody_data[] = {
    // Frase 1
    {D4, T_NOTE}, {E4, T_NOTE}, {FS4, T_NOTE}, {G4, T_NOTE}, {A4, T_NOTE}, {G4, T_NOTE}, {FS4, T_NOTE}, {E4, T_NOTE},
    
    // Repetición
    {D4, T_NOTE}, {E4, T_NOTE}, {FS4, T_NOTE}, {G4, T_NOTE}, {A4, T_NOTE}, {G4, T_NOTE}, {FS4, T_NOTE}, {E4, T_NOTE},
    
    // Frase 2
    {G4, T_NOTE}, {A4, T_NOTE}, {B4, T_NOTE}, {C5, T_NOTE}, {B4, T_NOTE}, {A4, T_NOTE}, {G4, T_NOTE},
    
    // Frase 3
    {G4, T_NOTE}, {A4, T_NOTE}, {B4, T_NOTE}, {C5, T_NOTE}, {B4, T_NOTE}, {A4, T_NOTE}, {G4, T_NOTE},
    {G4, T_NOTE}, {A4, T_NOTE}, {B4, T_NOTE}, {C5, T_NOTE}, {B4, T_NOTE}, {A4, T_NOTE}, {G4, T_NOTE},
    
    // Frase 4
    {G4, T_NOTE}, {A4, T_NOTE}, {B4, T_NOTE}, {C5, T_NOTE}, {B4, T_NOTE}, {A4, T_NOTE}, {G4, T_NOTE},
    {A4, T_NOTE}, {B4, T_NOTE}, {C5, T_NOTE}, {D5, T_NOTE}, {E5, T_NOTE}, {FS5, T_NOTE}, {G5, T_NOTE}, {FS5, T_NOTE}, {E5, T_NOTE},
    
    // Cierre
    {C5, T_NOTE}, {D5, T_NOTE}, {E5, T_NOTE}, {FS5, T_NOTE}, {G5, T_NOTE}, {A5, T_NOTE}, {G5, T_NOTE}, {FS5, T_NOTE}, {E5, T_NOTE}
};

const uint32_t MELODY_LENGTH = sizeof(melody_data) / sizeof(Note);

#endif // SAMPLE_H