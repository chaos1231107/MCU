
// 14.7mhz 로 동작
#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRB = 0xff;
    while (1) 
    {
		PORTB = 0xff;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);
    }
	return 0;
}
