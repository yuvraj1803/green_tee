#ifndef __PL011_H__
#define __PL011_H__

#define PL011_BASE	0x9040000
#define PL011_LIMIT	0x9041000
#define APB_CLOCK_FQ	0x16E3600	// 24-MHz
#define PL011_BAUDRATE	115200

#define PL011_UARTDR		(PL011_BASE + 0x00)
#define PL011_UARTRSR		(PL011_BASE + 0x04)

#define PL011_UARTFR		(PL011_BASE + 0x18)
#define PL011_UARTFR_BUSY	(1U << 3)

#define PL011_UARTILPR		(PL011_BASE + 0x20)
#define PL011_UARTIBRD		(PL011_BASE + 0x24)
#define PL011_UARTFBRD		(PL011_BASE + 0x28)

#define PL011_UARTLCRH		(PL011_BASE + 0x2C)
#define PL011_UARTLCRH_FEN	(1U << 4)
#define PL011_UARTLCRH_STP2	(1U << 3)
#define PL011_UARTLCRH_WLEN	(1U << 5)

#define PL011_UARTCR		(PL011_BASE + 0x30)
#define PL011_UARTCR_UARTEN	(1U << 0)
#define PL011_UARTCR_TXE	(1U << 8)
#define PL011_UARTCR_RXE	(1U << 9)

#define PL011_UARTIFLS  	(PL011_BASE + 0x34)
#define PL011_UARTIMSC		(PL011_BASE + 0x38)
#define PL011_UARTRIS		(PL011_BASE + 0x3C)
#define PL011_UARTMIS   	(PL011_BASE + 0x40)
#define PL011_UARTICR		(PL011_BASE + 0x44)
#define PL011_UARTDMACR		(PL011_BASE + 0x48)

#define PL011_PREINIT_BUFFER_SIZE 512

void pl011_init(void);
void pl011_write(char* str);
void pl011_write_hex(unsigned long long x);
void pl011_putc(char c);
#endif
