#ifndef UART_H
#define UART_H
#include <stdint.h>

typedef struct { 
    // Tasks
    volatile uint32_t TASKS_STARTRX;   // 0x000 Start UART receiver
    volatile uint32_t TASKS_STOPRX;    // 0x004 Stop UART receiver
    volatile uint32_t TASKS_STARTTX;   // 0x008 Start UART transmitter
    volatile uint32_t TASKS_STOPTX;    // 0x00C Stop UART transmitter
    volatile uint32_t RESERVED0[3];    // 0x010 - 0x018 Reserved
    volatile uint32_t TASKS_SUSPEND;   // 0x01C Suspend UART

    volatile uint32_t RESERVED1[56];   // 0x020 - 0x0FC Reserved

    // Events
    volatile uint32_t EVENTS_CTS;      // 0x100
    volatile uint32_t EVENTS_NCTS;     // 0x104
    volatile uint32_t EVENTS_RXDRDY;   // 0x108
    volatile uint32_t RESERVED2[4];    // 0x10C - 0x11C reserved
    volatile uint32_t EVENTS_TXDRDY;   // 0x11C
    volatile uint32_t RESERVED3[1];    // 0x120 reserved
    volatile uint32_t EVENTS_ERROR;    // 0x124
    volatile uint32_t RESERVED4[7];   // 0x128 - 0x144 reserved
    volatile uint32_t EVENTS_RXTO;     // 0x144

    volatile uint32_t RESERVED6[46];   // 0x148 - 0x1FC Reserved

    // Shortcuts
    volatile uint32_t SHORTS;          // 0x200 Shortcut register
    volatile uint32_t RESERVED7[64];   // 0x204 - 0x300 Reserved

    // Interrupts
    volatile uint32_t INTENSET;        // 0x304 Enable interrupt
    volatile uint32_t INTENCLR;        // 0x308 Disable interrupt
    volatile uint32_t RESERVED8[93];   // 0x30C - 0x47F Reserved

    // Error
    volatile uint32_t ERRORSRC;        // 0x480 Error source
    volatile uint32_t RESERVED9[31];   // 0x484 - 0x4FF Reserved

    // Enable
    volatile uint32_t ENABLE;          // 0x500 Enable UART

    // Pin select
    volatile uint32_t RESEVED[1];      // 0x504 RTS pin
    volatile uint32_t PSELRTS;         // 0x508 RTS pin
    volatile uint32_t PSELTXD;         // 0x50C TXD pin
    volatile uint32_t PSELCTS;         // 0x510 CTS pin
    volatile uint32_t PSELRXD;         // 0x514 RXD pin

    // Data registers
    volatile uint32_t RXD;             // 0x518 RXD
    volatile uint32_t TXD;             // 0x51C TXD

    // Baud rate
    volatile uint32_t RESERVED10[1];   // 0x520
    volatile uint32_t BAUDRATE;        // 0x524

    volatile uint32_t RESERVED11[17];  // 0x528 - 0x56C Reserved

    // Configuration
    volatile uint32_t CONFIG;          // 0x56C
} NRF_UART_REG;

void uart_init();
void uart_send(char letter);
char uart_read();

#endif
