#include <stdint.h>
#include <stdio.h>

// ref p. 116 in nRF52832_product_specification-1.pdf
#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

void button_init(){ 
	// We set c (with bit offset 2) to 3: "Pull up on pin". ref p. 145 in nRF52832_product_specification-1.pdf
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
	GPIO->PIN_CNF[15] = (3 << 2); 
	GPIO->PIN_CNF[16] = (3 << 2);
	// Fill inn the configuration for the remaining buttons 
}

int main(){
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i); // pin set as output
		GPIO->OUTCLR = (1 << i); // writing a '1' sets the pin low; writing a '0' has no effect. This turns on the matrix
	}

	// Configure buttons -> see button_init()
	button_init();

	int sleep = 0;
	while(1){

		/* Check if button 1 is pressed;
		* turn on LED matrix if it is. */
		uint32_t button_1_is_off = GPIO->IN & (1 << 13);
		if (!button_1_is_off) {
			GPIO->OUT = GPIO->OUT & ~(0b1111 << 17);
		}
		
		/* Check if button 2 is pressed;
		* turn off LED matrix if it is. */
		uint32_t button_2_is_off = GPIO->IN & (1 << 14);
		if (!button_2_is_off) {
			GPIO->OUT = GPIO->OUT | 0b1111 << 17;
		}

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
