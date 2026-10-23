#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main()
{
    stdio_init_all();

    // regulator in PWM mode = less ADC noise
    gpio_init(23);
    gpio_set_dir(23, GPIO_OUT);
    gpio_put(23, 1);

    adc_init();
    adc_gpio_init(26);   // GP26 as analog input
    adc_select_input(0); // ADC0 = GP26

    while (true)
    {
        uint16_t lo = 4095, hi = 0;
        absolute_time_t end = make_timeout_time_ms(50);
        while (!time_reached(end))
        {
            uint16_t v = adc_read(); // 12-bit, 0–4095
            if (v < lo)
                lo = v;
            if (v > hi)
                hi = v;
        }
        printf("%u\n", hi - lo); // peak-to-peak
    }
}