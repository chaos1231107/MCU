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

volatile int t_cnt1 = 0, m_cnt1=0;
volatile int t_cnt2 = 0, m_cnt2=0;

void Segment(int N, int M){
	int i, Buff1, Buff2 ;
	unsigned int  N10, N1, M10, M1;
	
	
	Buff1 = N%100;
	Buff2 = M%100;

	N10 = Buff1 /10;
	N1 =  Buff1 % 10;
	
	M10 = Buff2 /10;
	M1 =  Buff2 % 10;

	for(i=0; i<30; i++){
		PORTC = 0x0e;
		PORTA = Font[N10];
		_delay_ms(1);

		PORTC = 0x0d;
		PORTA = Font[N1];
		_delay_ms(1);

		PORTC = 0x0b;
		PORTA = Font[M10];
		_delay_ms(1);

		PORTC = 0x07;
		PORTA = Font[M1];
		_delay_ms(1);
	}
}

ISR(TIMER0_OVF_vect){
	TCNT0 = 0xC6;
	t_cnt1++;
	
	if(t_cnt1 >= 125) {
		t_cnt1 = 0;
		m_cnt1++;
	}
}
ISR(TIMER2_OVF_vect){
	TCNT2 = 0x7A;
	t_cnt2++;
	
	if(t_cnt2 >= 100){
		t_cnt2= 0;
		m_cnt2++;
	}
}

int main(){
	DDRA = 0xff;
	DDRC = 0x0f;
	PORTA = 0xff;
	PORTC = 0x0f;
	ASSR = 0;

    TCCR0 = 0x05;
    TIMSK = 0x41;
    TCNT0 = 0xC6;
    TIFR = 0;
	
	TCCR2 = 0x05;
	TIMSK = 0x41;
	TCNT2 = 0xf2;
	TIFR = 0;

	sei();

	while(1){
		Segment(m_cnt1, m_cnt2);
	}
	return 0;
}
