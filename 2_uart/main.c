#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"

void button_init(){ 
	// We set c (with bit offset 2) to 3: "Pull up on pin". ref p. 145 in nRF52832_product_specification-1.pdf
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
	GPIO->PIN_CNF[15] = (3 << 2); 
	GPIO->PIN_CNF[16] = (3 << 2);
	// Fill inn the configuration for the remaining buttons 
}

int main(){
	button_init();
	uart_init();

	int sleep = 0;
	while(1){
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

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
