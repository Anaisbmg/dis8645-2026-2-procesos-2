// mux_pots.cpp
// read 3 potentiometers through a 3-bit analog mux (74HC4051 / CD4051 style)
// raspberry pi pico, plain pico sdk, c++

#include <cstdio>
#include <cstdlib>
#include "pico/stdlib.h"
#include "hardware/adc.h"

// ---- pin config: change these to match your board ----
constexpr uint PIN_S0 = 2;        // mux selector bit 0
constexpr uint PIN_S1 = 3;        // mux selector bit 1
constexpr uint PIN_S2 = 4;        // mux selector bit 2
constexpr uint PIN_MUX_OUT = 26;  // mux output -> GPIO26 (ADC0)

constexpr uint ADC_INPUT = PIN_MUX_OUT - 26;  // GPIO26..28 -> ADC0..2
constexpr uint NUM_POTS = 3;                  // pots on mux channels 0, 1, 2
constexpr uint SETTLE_US = 10;                // time for the mux + adc to settle

// ---- noise filtering ----
constexpr uint OVERSAMPLE = 16;   // adc readings averaged per pot read
constexpr int SMOOTH_SHIFT = 2;   // moving average weight: 1 / 2^SMOOTH_SHIFT (bigger = smoother, slower)
constexpr int HYSTERESIS = 6;     // ignore changes smaller than this (0..4095 units)

constexpr uint32_t SELECT_MASK = (1u << PIN_S0) | (1u << PIN_S1) | (1u << PIN_S2);

class MuxPots {
public:
    void begin() {
#ifdef PICO_SMPS_MODE_PIN
        // force the on-board power supply into pwm mode: less ripple, less adc noise
        gpio_init(PICO_SMPS_MODE_PIN);
        gpio_set_dir(PICO_SMPS_MODE_PIN, GPIO_OUT);
        gpio_put(PICO_SMPS_MODE_PIN, 1);
#endif

        // selector pins as outputs
        gpio_init(PIN_S0);
        gpio_init(PIN_S1);
        gpio_init(PIN_S2);
        gpio_set_dir_out_masked(SELECT_MASK);

        // adc on the mux output
        adc_init();
        adc_gpio_init(PIN_MUX_OUT);
        adc_select_input(ADC_INPUT);

        select(0);

        // start the filters at the current pot positions
        for (uint i = 0; i < NUM_POTS; i++) {
            uint16_t raw = read(i);
            smoothed[i] = raw << SMOOTH_SHIFT;
            stable[i] = raw;
        }
    }

    // set all three selector bits at the same time
    void select(uint channel) {
        uint32_t value = ((channel >> 0) & 1u) << PIN_S0 |
                         ((channel >> 1) & 1u) << PIN_S1 |
                         ((channel >> 2) & 1u) << PIN_S2;
        gpio_put_masked(SELECT_MASK, value);
        sleep_us(SETTLE_US);
    }

    // average of OVERSAMPLE readings, returns 0..4095
    uint16_t read(uint channel) {
        select(channel);
        adc_read();         // throw away first reading after switching
        uint32_t sum = 0;
        for (uint i = 0; i < OVERSAMPLE; i++) {
            sum += adc_read();
        }
        return sum / OVERSAMPLE;
    }

    // filtered values: averaged, smoothed and with hysteresis, 0..4095
    void readAll(uint16_t* values) {
        for (uint i = 0; i < NUM_POTS; i++) {
            int raw = read(i);

            // exponential moving average, kept scaled up by 2^SMOOTH_SHIFT to avoid losing precision
            smoothed[i] += raw - (smoothed[i] >> SMOOTH_SHIFT);
            int value = smoothed[i] >> SMOOTH_SHIFT;

            // only accept the new value if it moved far enough, or reached an end of the pot
            if (abs(value - stable[i]) >= HYSTERESIS || value == 0 || value == 4095) {
                stable[i] = value;
            }
            values[i] = stable[i];
        }
    }

private:
    int smoothed[NUM_POTS];
    int stable[NUM_POTS];
};

int main() {
    stdio_init_all();

    MuxPots pots;
    pots.begin();

    uint16_t values[NUM_POTS];

    while (true) {
        pots.readAll(values);
        printf("pot0: %4u  pot1: %4u  pot2: %4u\n", values[0], values[1], values[2]);
        sleep_ms(50);
    }
}
