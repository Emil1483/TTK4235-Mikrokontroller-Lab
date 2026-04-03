#include "gpio.h"

void configure_led_matrix() {
    for (int i = 17; i <= 20; i++) {
        GPIO->DIRSET = (1 << i); // pin set as output

        // writing a '1' sets the pin high; This turns off the matrix
        GPIO->OUTSET = (1 << i);
    }
}

void configure_button() {
    // Configure pin 13 to be input, connected to input buffer, pull up,
    // standard '0' and '1', and disabled sense
    GPIO->PIN_CNF[13] = 3 << 2;
}