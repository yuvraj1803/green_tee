ENTRY(_start)

SECTIONS{
	. = 0xe100000;
	__tee_begin = .;	
	.text.boot : {*(.text.boot)}
	. = ALIGN(0x1000);

	.text	   : {*(.text)}
	. = ALIGN(0x1000);

	.rodata    : {*(.rodata)}
	. = ALIGN(0x1000);

	__bss_begin = .;
	.bss	   : {*(.bss)}
	__bss_end = .;

	. = ALIGN(0x1000);
	__tee_end = .;

	__tee_limit = 0xf000000;
}
