#include <drivers/pl011.h>
#include <mm/io.h>

static int pl011_active = 0;

void pl011_wait(void){
	while(io_read32(PL011_UARTFR) & PL011_UARTFR_BUSY);
}

void pl011_disable(void){
	uint32_t uartcr = io_read32(PL011_UARTCR);
	io_write32(PL011_UARTCR, uartcr & ~PL011_UARTCR_UARTEN);	
	pl011_active = 0;
}

void pl011_enable(void){
        uint32_t uartcr = io_read32(PL011_UARTCR);
        io_write32(PL011_UARTCR, uartcr | PL011_UARTCR_UARTEN);
	pl011_active = 1;
}

void pl011_flush(void){
	uint32_t lcrh = io_read32(PL011_UARTLCRH);
	io_write32(PL011_UARTLCRH, lcrh & ~PL011_UARTLCRH_FEN);
}

void pl011_set_uartlcrh(void){
	// we will be using 8-bits wide data and 2 stop bits.
	uint32_t uartlcrh = io_read32(PL011_UARTLCRH);
	io_write32(PL011_UARTLCRH, uartlcrh | PL011_UARTLCRH_STP2 | (0b11 * PL011_UARTLCRH_WLEN));
}

void pl011_set_uartcr(void){
	
	uint32_t uartcr = io_read32(PL011_UARTCR);
	io_write32(PL011_UARTCR, uartcr | PL011_UARTCR_TXE);

}

void pl011_set_baudrate(void){

	// easy way to extract the fractional part is to calculate divisor with a bigger multiple.
	// fractional part can be extracted by lower significant bits.
	uint32_t baudrate_adjusted = 64*(APB_CLOCK_FQ / (16 * PL011_BAUDRATE));

	uint32_t baudrate_divisor = (baudrate_adjusted / 64) & 0xFFFF;
	uint32_t baudrate_fractional = (baudrate_adjusted & 0x3F);

	io_write32(PL011_UARTIBRD, baudrate_divisor);
	io_write32(PL011_UARTFBRD, baudrate_fractional);

}

void pl011_mask_all_interrupts(void){
	io_write32(PL011_UARTIMSC, 0x7F);
}

void pl011_putc(char c){
	if(!pl011_active) return;

	pl011_wait();
	
	if(c == '\n') c = '\r';

	io_write32(PL011_UARTDR, c & 0xFF);

	pl011_wait();

}


void pl011_init(void){
		
	pl011_disable();
	pl011_wait();
	pl011_flush();
	pl011_set_baudrate();
	pl011_set_uartlcrh();
	pl011_set_uartcr();
	pl011_mask_all_interrupts();
	pl011_enable();
}
