#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/audio_i2s.h"

// Pines I2S
#define PIN_I2S_DATA        28 // DIN
#define PIN_I2S_CLOCK_BASE  26 // BCLK = 26, LRC = 27

#define SAMPLE_RATE         44100
#define BUFFER_SAMPLES      256
#define VOLUME              5000 // Nivel de amplitud seguro para pruebas

// Frecuencias de notas musicales (en Hz)
#define REST   0.0f
#define D3     146.83f
#define DS3    155.56f
#define E3     164.81f
#define F3     174.61f
#define FS3    185.00f
#define G3     196.00f
#define GS3    207.65f
#define A3     220.00f
#define AS3    233.08f
#define B3     246.94f
#define C4     261.63f
#define CS4    277.18f
#define D4     293.66f
#define DS4    311.13f
#define E4     329.63f
#define F4     349.23f
#define FS4    369.99f
#define G4     392.00f
#define GS4    415.30f
#define A4     440.00f
#define AS4    466.16f
#define B4     493.88f
#define C5     523.25f
#define CS5    554.37f
#define D5     587.33f
#define DS5    622.25f
#define E5     659.25f

// Duraciones relativas (a ~185 BPM, una semicorchea dura aprox. 81 ms)
#define T_16TH   81
#define T_8TH    162
#define T_QTR    324
#define T_HALF   648

struct Note {
    float freq;
    uint32_t duration_ms;
};

// Transcripción de la Intro y Tema Principal de Gym Leader Battle (Pokémon R/B/Y)
const Note melody[] = {
    // --- INTRO: Riff cromático descendente y ascendente clásico ---
    {E4, T_16TH}, {DS4, T_16TH}, {D4, T_16TH}, {CS4, T_16TH},
    {C4, T_16TH}, {B3, T_16TH},  {AS3, T_16TH}, {A3, T_16TH},
    {GS3, T_16TH}, {G3, T_16TH}, {FS3, T_16TH}, {F3, T_16TH},
    {E3, T_8TH},  {E3, T_16TH},  {G3, T_16TH},  {AS3, T_8TH},

    {E4, T_16TH}, {DS4, T_16TH}, {D4, T_16TH}, {CS4, T_16TH},
    {C4, T_16TH}, {B3, T_16TH},  {AS3, T_16TH}, {A3, T_16TH},
    {GS3, T_16TH}, {G3, T_16TH}, {FS3, T_16TH}, {F3, T_16TH},
    {B3, T_8TH},  {AS3, T_8TH},  {G3, T_8TH},   {E3, T_8TH},

    // Subida tensa previa a la melodía
    {E3, T_16TH}, {G3, T_16TH}, {B3, T_16TH}, {E4, T_16TH},
    {G4, T_16TH}, {E4, T_16TH}, {B3, T_16TH}, {G3, T_16TH},
    {DS4, T_16TH}, {FS4, T_16TH}, {B4, T_8TH}, {REST, T_16TH},

    // --- TEMA A (Melodía de combate) ---
    {E4, T_8TH}, {B3, T_16TH}, {E4, T_16TH}, {G4, T_8TH}, {FS4, T_8TH},
    {E4, T_8TH}, {D4, T_16TH}, {E4, T_16TH}, {B3, T_QTR},
    
    {E4, T_8TH}, {B3, T_16TH}, {E4, T_16TH}, {G4, T_8TH}, {A4, T_8TH},
    {B4, T_8TH}, {A4, T_8TH},  {G4, T_8TH},  {FS4, T_8TH},

    {E4, T_8TH}, {B3, T_16TH}, {E4, T_16TH}, {G4, T_8TH}, {FS4, T_8TH},
    {E4, T_8TH}, {G4, T_16TH}, {B4, T_16TH}, {D5, T_QTR},

    {C5, T_8TH}, {B4, T_8TH},  {A4, T_8TH},  {G4, T_8TH},
    {FS4, T_8TH}, {E4, T_8TH}, {DS4, T_QTR},

    // Cadencia rítmica
    {E4, T_16TH}, {E4, T_16TH}, {REST, T_16TH}, {E4, T_16TH},
    {G4, T_8TH},  {FS4, T_8TH}, {E4, T_QTR},
    {REST, T_QTR}
};

const size_t TOTAL_NOTES = sizeof(melody) / sizeof(Note);

int main() {
    stdio_init_all();

    static audio_format_t audio_format = {
        .sample_freq = SAMPLE_RATE,
        .format = AUDIO_BUFFER_FORMAT_PCM_S16,
        .channel_count = 2,
    };

    static audio_buffer_format_t producer_format = {
        .format = &audio_format,
        .sample_stride = 4
    };

    struct audio_i2s_config config = {
        .data_pin = PIN_I2S_DATA,
        .clock_pin_base = PIN_I2S_CLOCK_BASE,
        .dma_channel = 0,
        .pio_sm = 0,
    };

    struct audio_buffer_pool *producer_pool = audio_new_producer_pool(
        &producer_format, 3, BUFFER_SAMPLES);

    audio_i2s_setup(&audio_format, &config);
    audio_i2s_connect(producer_pool);
    audio_i2s_set_enabled(true);

    float phase = 0.0f;
    size_t note_idx = TOTAL_NOTES - 1;
    uint32_t samples_left_in_note = 0;

    while (true) {
        struct audio_buffer *buffer = take_audio_buffer(producer_pool, true);
        int16_t *samples = (int16_t *)buffer->buffer->bytes;

        for (uint16_t i = 0; i < BUFFER_SAMPLES; i++) {
            // Avanzar a la siguiente nota si la actual terminó
            if (samples_left_in_note == 0) {
                note_idx = (note_idx + 1) % TOTAL_NOTES;
                samples_left_in_note = (melody[note_idx].duration_ms * SAMPLE_RATE) / 1000;
            }

            float current_freq = melody[note_idx].freq;
            int16_t sample_val = 0;

            if (current_freq > 0.0f) {
                // Síntesis de onda de pulso (duty cycle 50% estilo Game Boy)
                sample_val = (phase < 0.5f) ? VOLUME : -VOLUME;

                // Avanzar fase de 0.0 a 1.0
                phase += current_freq / (float)SAMPLE_RATE;
                if (phase >= 1.0f) phase -= 1.0f;
            } else {
                // Silencio
                sample_val = 0;
                phase = 0.0f;
            }

            samples[i * 2]     = sample_val;
            samples[i * 2 + 1] = sample_val;

            samples_left_in_note--;
        }

        buffer->sample_count = BUFFER_SAMPLES;
        give_audio_buffer(producer_pool, buffer);
    }

    return 0;
}