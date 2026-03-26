#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)


void uart_init() {
    // Set RXD to input pin and configure it to "pull up"
    GPIO->PIN_CNF[8] = 3 << 2;
    
    // Set TXD to output pin   
    GPIO->PIN_CNF[6] = 1;

    // Disable CTS and RTS. We dont have access to them
    UART->PSELCTS =  0xFFFFFFFF;
    UART->PSELRTS =  0xFFFFFFFF;
    UART->PSELRXD = 8;
    UART->PSELTXD = 6;

    // Set baudrate to 9600
    UART->BAUDRATE = 0x00275000;

    // Start the UART module
    UART->ENABLE = 4;

    // Start recieving messages
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter) {
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;

    while (1) {
        uint32_t value = UART->EVENTS_TXDRDY;
        if (value != 0) break;
    }

    //while (UART->EVENTS_TXDRDY == 0);
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STOPTX = 1;

}

char uart_read() {
    if (!(UART->EVENTS_RXDRDY)) return '\0';
    UART->EVENTS_RXDRDY = 0;
    char result = UART->RXD;
    return result;
}