#define F_CPU 14745600UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(){
	int i;
	DDRA = 0x0f;

	while(1){
		//1바튀 = 20클럭
		//1미터 -> 대략 7바퀴 = 140 클럭
		//i = 140/4 == 35
		for (i=0; i<35; i++){
			PORTA = 0x03;
			_delay_ms(10);

			PORTA = 0x09;
			_delay_ms(10);

			PORTA = 0x0C;
			_delay_ms(10);

			PORTA = 0x06;
			_delay_ms(10);
		}
		_delay_ms(3000);
	}
	return 0;
}
