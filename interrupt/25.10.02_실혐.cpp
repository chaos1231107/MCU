#define F_CPU 14745600UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// 7-세그먼트 숫자 폰트
unsigned char Font[18] = {
	0x3F, 0x06, 0x5B, 0x4F,
	0x66, 0x6D, 0x7C, 0x07,
	0x7F, 0x67, 0x77, 0x7C,
	0x39, 0x5E, 0x79, 0x71,
	0x08, 0x80
};

// 인터럽트용 카운터 변수
volatile unsigned char count0 = 0;
volatile unsigned char count1 = 0;

// 7-세그먼트 4자리 표시 함수
void DecSegment(unsigned char left, unsigned char right) {
	int i;
	unsigned char L10 = left / 10;
	unsigned char L1  = left % 10;
	unsigned char R10 = right / 10;
	unsigned char R1  = right % 10;

	for (i = 0; i < 30; i++) {
		// 1st Digit (왼쪽 첫 번째)
		PORTG = 0b1110;
		PORTB = Font[L10];
		_delay_ms(1);

		// 2nd Digit (왼쪽 두 번째)
		PORTG = 0x0D;
		PORTB = Font[L1];
		_delay_ms(1);

		// 3rd Digit (오른쪽 첫 번째)
		PORTG = 0x0B;
		PORTB = Font[R10];
		_delay_ms(1);

		// 4th Digit (오른쪽 두 번째)
		PORTG = 0x07;
		PORTB = Font[R1];
		_delay_ms(1);
	}
}

// INT0 - 하강 에지 (스위치 1)
ISR(INT0_vect) {
	if (count0 < 99) count0++;
}

// INT1 - 상승 에지 (스위치 2)
ISR(INT1_vect) {
	if (count1 < 99) count1++;
}

int main(void) {
	// 포트 설정
	DDRB = 0xFF; // PORTB: 출력 (7-세그먼트 데이터)
	DDRG = 0xFF; // PORTG: 출력 (디지트 선택)
	DDRD = 0x00; // PORTD: 입력 (INT0, INT1 스위치)

	// 인터럽트 감지 설정
	EICRA = (1 << ISC01) |       // INT0: 하강 에지
	(1 << ISC11) | (1 << ISC10); // INT1: 상승 에지

	EIMSK = (1 << INT0) | (1 << INT1); // INT0, INT1 인터럽트 허용

	sei(); // 전역 인터럽트 허용

	while (1) {
		DecSegment(count0, count1);
	}

	return 0;
}
