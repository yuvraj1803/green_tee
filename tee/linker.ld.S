ENTRY(_start)

SECTIONS{
	. = 0xe100000;
	__tee_begin = .;	
	__tee_asm_text_begin = .;
	.text.asm : {*(.text.asm)}
	. = ALIGN(0x1000);
	__tee_asm_text_end = .;


	__tee_text_begin = .;
	.text	   : {*(.text)}
	. = ALIGN(0x1000);
	__tee_text_end = .;


	__tee_data_begin = .;
	.data	   : {*(.data)}
	. = ALIGN(0x1000);
	__tee_data_end = .;


	__tee_rodata_begin = .;
	.rodata    : {*(.rodata)}
	. = ALIGN(0x1000);
	__tee_rodata_end = .;


	__bss_begin = .;
	.bss	   : {*(.bss)}
	. = ALIGN(0x1000);
	__bss_end = .;

	__tee_end = .;
	

	__tee_stack_base = __tee_limit;
	__tee_limit = 0xf000000;
}
