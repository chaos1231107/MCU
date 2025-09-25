#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char Font[18] = {
	0x3F, 0X06, 0X5B, 0X4F,
	0X66, 0X6D, 0X7C, 0X07,
	0X7F, 0X67, 0X77, 0X7C,
	0X39, 0X5E, 0X79, 0X71,
	0X08, 0X80};

void Segment(unsigned char N){
	int  i;
	unsigned char  N10, N1;
		
	N10 = N /16;  
	N1 = N % 16;
	
	for(i=0; i < 30; i++){
		PORTG = 0x0e;
		PORTB = Font[N10];
		_delay_ms(1);

		PORTG = 0x0d;
		PORTB = Font[N1];
		_delay_ms(1);
	}
}

int main(){
	unsigned char Dip_sw ;

	DDRE = 0xff;
	DDRD = 0x00;

	DDRB = 0xff;
	DDRG = 0xff;
	
	while(1){
		Dip_sw = PIND;
		PORTE = Dip_sw;
		Segment(Dip_sw);	
	}
	return 0;
}
