#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char Font[16] = {
	0x3F,0x06,0x5B,0x4F,
	0x66,0x6D,0x7D,0x07,
	0x7F,0x6F,0x77,0x7C,
	0x39,0x5E,0x79,0x71
};

void DisplayDecimal(unsigned char N) {
	unsigned char N10 = N / 10;
	unsigned char N1 = N % 10;

	for (int i=0; i<40; i++) {
		PORTG = 0x0E;   // 왼쪽 첫번째
		PORTB = Font[N10];
		_delay_ms(1);

		PORTG = 0x0D;    // 왼쪽 두번째
		PORTB = Font[N1];
		_delay_ms(1);
	}
}

int main(void) {
	unsigned char R_sw;

	DDRD = 0x00;  // 스위치 입력
	DDRB = 0xFF;  // 7-세그먼트 출력
	DDRG = 0xFF;  

	while (1) {
		R_sw = PIND & 0x0F;   
		DisplayDecimal(R_sw); //숫자 출력
	}
	return 0;
}
