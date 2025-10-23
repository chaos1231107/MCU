#define F_CPU 14745600UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char Font[18] = {
	0x3F, 0X06, 0X5B, 0X4F,
	0X66, 0X6D, 0X7C, 0X07,
	0X7F, 0X67, 0X77, 0X7C,
	0X39, 0X5E, 0X79, 0X71,
	0X08, 0X80
};

volatile int t_cnt = 0, m_cnt = 0;

void Segment(int N){
	int i, Buff;
	unsigned char N1000, N100, N10, N1;

	N1000 = N /1000;
	Buff = N % 1000;

	N100 = Buff / 100;
	Buff = Buff % 100;

	N10 = Buff /10;
	N1 =  Buff % 10;

	for(i=0; i<30; i++){
		PORTC = 0x0e;
		PORTA = Font[N1000];
		_delay_ms(1);

		PORTC = 0x0d;
		PORTA = Font[N100];
		_delay_ms(1);

		PORTC = 0x0b;
		PORTA = Font[N10];
		_delay_ms(1);

		PORTC = 0x07;
		PORTA = Font[N1];
		_delay_ms(1);
	}
}

ISR(TIMER2_COMP_vect){
	t_cnt++ ;
	
	if( t_cnt >=100){
		m_cnt= m_cnt+5;
		t_cnt = 0;
	}
}

int main(){
	DDRA = 0xff;
	DDRC = 0xff;
	PORTA = 0xff;
	PORTC = 0x0f;

	ASSR = 0;
	TCCR2 = 0x0d;
	TIMSK = 0x80;

	TCNT2 = 0x00;
	OCR2 = 72;
	TIFR = 0;

	sei();

	while(1){
		Segment(m_cnt);
	}
	return 0;
}
