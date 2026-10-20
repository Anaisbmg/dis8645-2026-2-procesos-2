#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/audio_i2s.h"

// Incluimos tu partitura
#include "sample.h"

#define PIN_I2S_DATA        28
#define PIN_I2S_CLOCK_BASE  26
#define BUFFER_SAMPLES      256
#define VOLUME              5000 

int main() {
    // Inicializar consola
    stdio_init_all();

    // Pausa de 2 segundos para darte tiempo a abrir el Monitor Serial en VS Code
    sleep_ms(2000);
    printf("\n--- Iniciando Sintetizador Pokémon ---\n");

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

    printf("1. Configurando hardware I2S a %d Hz...\n", SAMPLE_RATE);
    audio_i2s_setup(&audio_format, &config);
    
    printf("2. Conectando buffers...\n");
    audio_i2s_connect(producer_pool);
    audio_i2s_set_enabled(true);

    printf("3. Hardware iniciado correctamente. Entrando al bucle de audio...\n");

    float phase = 0.0f;
    size_t note_idx = 0;
    uint32_t samples_left_in_note = (melody_data[note_idx].duration_ms * SAMPLE_RATE) / 1000;

    // Contador para no saturar la consola imprimiendo cada milisegundo
    uint32_t debug_counter = 0;

    while (true) {
        // Si la librería falla, el código se quedará congelado en esta línea para siempre:
        struct audio_buffer *buffer = take_audio_buffer(producer_pool, true);
        
        int16_t *samples = (int16_t *)buffer->buffer->bytes;

        for (uint16_t i = 0; i < BUFFER_SAMPLES; i++) {
            if (samples_left_in_note == 0) {
                note_idx = (note_idx + 1) % MELODY_LENGTH;
                samples_left_in_note = (melody_data[note_idx].duration_ms * SAMPLE_RATE) / 1000;
            }

            float current_freq = melody_data[note_idx].freq;
            int16_t sample_val = 0;

            uint32_t total_note_samples = (melody_data[note_idx].duration_ms * SAMPLE_RATE) / 1000;
            bool is_playing = samples_left_in_note > (total_note_samples / 10); 

            if (current_freq > 0.0f && is_playing) {
                sample_val = (phase < 0.5f) ? VOLUME : -VOLUME;
                phase += current_freq / (float)SAMPLE_RATE;
                if (phase >= 1.0f) phase -= 1.0f;
            } else {
                phase = 0.0f;
            }

            samples[i * 2]     = sample_val;
            samples[i * 2 + 1] = sample_val;
            samples_left_in_note--;
        }

        buffer->sample_count = BUFFER_SAMPLES;
        give_audio_buffer(producer_pool, buffer);

        // Imprimir señal de vida cada cierto tiempo (~1 segundo)
        debug_counter++;
        if (debug_counter % (SAMPLE_RATE / BUFFER_SAMPLES) == 0) {
            printf("Sonando nota actual index: %d (Frecuencia: %.1f Hz)\n", note_idx, melody_data[note_idx].freq);
        }
    }

    return 0;
}