#include <drivers/pl011.h>
#include <stdarg.h>
#include <lib/stdlib.h>

void printf(char* fmt, ...){
	va_list ap;
	va_start(ap, fmt);

	for(char*p = fmt; *p; p++){
		if(*p != '%'){
			pl011_putc(*p);
		}else{
			int val;
			switch(*++p){
				case 'x':
					val = va_arg(ap, int);
					pl011_write_hex(val);
					break;
				case 's':
					char* str = va_arg(ap, char*);
					pl011_write(str);
					break;
				case 'd':
				    val = va_arg(ap, long long);
					pl011_write(itoa(val));
					break;
				case 'c':
					val = va_arg(ap, int);
					pl011_putc(val);
					break;
				default:
					break;
			}
		}
	}
}

void LOG(char* str){
	pl011_write("[LOG]: ");
	pl011_write(str);
}
