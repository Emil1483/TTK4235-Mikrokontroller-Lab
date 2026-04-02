#include "gpio.h"
#include "uart.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void button_init() {
    // We set c (with bit offset 2) to 3: "Pull up on pin". ref p. 145 in
    // nRF52832_product_specification-1.pdf
    GPIO->PIN_CNF[13] = (3 << 2);
    GPIO->PIN_CNF[14] = (3 << 2);
    GPIO->PIN_CNF[15] = (3 << 2);
    GPIO->PIN_CNF[16] = (3 << 2);
    // Fill inn the configuration for the remaining buttons
}

void led_init() {
    for (int i = 17; i <= 20; i++) {
        GPIO->DIRSET = (1 << i); // pin set as output
        GPIO->OUTCLR = (1 << i); // writing a '1' sets the pin low; writing a
                                 // '0' has no effect. This turns on the matrix
    }
}

void led_on() {
    for (int i = 17; i <= 20; i++) {
        GPIO->OUTCLR = (1 << i); // writing a '1' sets the pin low; writing a
                                 // '0' has no effect. This turns on the matrix
    }
}

void led_off() {
    for (int i = 17; i <= 20; i++) {
        GPIO->OUTSET = (1 << i); // writing a '1' sets the pin high; writing a
                                 // '0' has no effect. This turns off the matrix
    }
}

int main() {
    button_init();
    uart_init();
    led_init();

    bool led_is_on = true;

    int sleep = 0;
    while (1) {
        /* Check if button 1 is pressed;
         * turn on LED matrix if it is. */
        uint32_t button_1_is_off = GPIO->IN & (1 << 13);
        if (!button_1_is_off) {
            uart_send('A');
        }

        /* Check if button 2 is pressed;
         * turn off LED matrix if it is. */
        uint32_t button_2_is_off = GPIO->IN & (1 << 14);
        if (!button_2_is_off) {
            uart_send('B');
        }

        if (uart_read() != '\0') {
            if (led_is_on) {
                led_off();
            } else {
                led_on();
            }
            led_is_on = !led_is_on;
        }

        sleep = 10000;
        while (--sleep)
            ;
    }
    return 0;
}
