#include "gpiote.h"

void configure_channels() {
    // Use one channel to listen to BUTTON 1

    // configure channel[0] to have mode set to event and PSEL set to pin 13 and
    // set polarity to LoToHi
    GPIOTE->CONFIG[0] = 1 | (13 << 8) | (1 << 16);

    // The rest of the channels should be configured as tasks and
    // should be connected to their pin for the LED-matrix. The pin will toggle
    // each time the task is fired.

    // configure channel 1-4 to have mode task, PSEL set to 17-20, polarity set
    // to toggle and set outinit to low
    for (int i = 1; i < 5; i++) {
        int pin = i + 16;
        GPIOTE->CONFIG[i] = 3 | (pin << 8) | (3 << 16) | (0 << 20);
    }
}