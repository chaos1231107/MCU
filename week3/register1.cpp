#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRE = 0xff;

	while(1){
		PORTE = 0x0c;
		_delay_ms(1000);

		PORTE = 0x03;
		_delay_ms(1000);

		PORTE = 0x30;
		_delay_ms(1000);
		
		PORTE = 0xc0;
		_delay_ms(1000);
		
	}
	return 0 ;
}
