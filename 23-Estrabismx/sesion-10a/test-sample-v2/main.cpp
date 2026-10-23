#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/audio_i2s.h"
#include "Fah.h"
#include "Grindr.h" 

#define PICO_AUDIO_I2S_DATA_PIN        28 
#define PICO_AUDIO_I2S_CLOCK_PIN_BASE  26 

#define BUTTON_FAH_PIN                 0
#define BUTTON_GRINDR_PIN              1

#define SAMPLE_RATE                    11025 
#define SAMPLES_PER_BUFFER             256

int main() {
    stdio_init_all();

    // Configuración de pines como entradas puras (depende del pull-down de tu protoboard)
    gpio_init(BUTTON_FAH_PIN);
    gpio_set_dir(BUTTON_FAH_PIN, GPIO_IN);

    gpio_init(BUTTON_GRINDR_PIN);
    gpio_set_dir(BUTTON_GRINDR_PIN, GPIO_IN);

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
        .data_pin = PICO_AUDIO_I2S_DATA_PIN,
        .clock_pin_base = PICO_AUDIO_I2S_CLOCK_PIN_BASE,
        .dma_channel = 0,
        .pio_sm = 0,
    };

    struct audio_buffer_pool *producer_pool = audio_new_producer_pool(
        &producer_format, 
        3, 
        SAMPLES_PER_BUFFER
    );

    audio_i2s_setup(&audio_format, &config);
    audio_i2s_connect(producer_pool);
    audio_i2s_set_enabled(true);

    const int16_t *current_sample_data = nullptr;
    uint32_t total_samples = 0;
    uint32_t sample_index = 0;
    bool is_playing = false;

    while (true) {
        // Lectura de botones (lógica activa en alto)
        if (gpio_get(BUTTON_FAH_PIN) && !is_playing) {
            current_sample_data = (const int16_t *)(fah + 44);
            total_samples = (sizeof(fah) - 44) / 2;
            sample_index = 0;
            is_playing = true;
            sleep_ms(200); // Antirrebote simple
        } else if (gpio_get(BUTTON_GRINDR_PIN) && !is_playing) {
            current_sample_data = (const int16_t *)(Grindr + 44);
            total_samples = (sizeof(Grindr) - 44) / 2;
            sample_index = 0;
            is_playing = true;
            sleep_ms(200); // Antirrebote simple
        }

        struct audio_buffer *buffer = take_audio_buffer(producer_pool, true);
        int16_t *samples = (int16_t *)buffer->buffer->bytes;

        for (uint16_t i = 0; i < SAMPLES_PER_BUFFER; i++) {
            int16_t val = 0;

            if (is_playing && current_sample_data != nullptr) {
                val = current_sample_data[sample_index++];
                if (sample_index >= total_samples) {
                    is_playing = false; 
                }
            }

            samples[i * 2]     = val; 
            samples[i * 2 + 1] = val; 
        }

        buffer->sample_count = SAMPLES_PER_BUFFER;
        give_audio_buffer(producer_pool, buffer);
    }

    return 0;
}