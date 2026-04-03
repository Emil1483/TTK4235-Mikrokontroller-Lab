#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main() {
    configure_led_matrix();
    configure_button();
    configure_gpiote_channels();
    configure_ppi_channels();

    while (1)
        ;

    return 0;
}