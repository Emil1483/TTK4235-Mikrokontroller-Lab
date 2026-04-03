#include "gpio.h"

void configure_led_matrix() {
    for (int i = 17; i <= 20; i++) {
        GPIO->DIRSET = (1 << i); // pin set as output

        // writing a '1' sets the pin high; This turns off the matrix
        GPIO->OUTSET = (1 << i);
    }
}