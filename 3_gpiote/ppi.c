#include "ppi.h"
#include "gpiote.h"

void configure_ppi_channels() {
    // configure channel
    // 0: EEP = GPIOTE->EVENTS_IN[0] TEP = GPIOTE->TASKS_OUT[1]
    // 1: EEP = GPIOTE->EVENTS_IN[0] TEP = GPIOTE->TASKS_OUT[2]
    // 2: EEP = GPIOTE->EVENTS_IN[0] TEP = GPIOTE->TASKS_OUT[3]
    // 3: EEP = GPIOTE->EVENTS_IN[0] TEP = GPIOTE->TASKS_OUT[4]
    for (int i = 0; i < 4; i++) {
        PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
        PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[i + 1]);
    }

    // enable channel 0-3
    PPI->CHENSET = 0b1111;
}