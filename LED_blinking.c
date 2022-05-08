/*
 * main.c
 *
 * Created: 3/23/2022 11:03:52 PM
 *  Author: Mehul
 */ 
#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0b00000001; //Pin B0 becomes output pin
    PORTB = 0b00000000; //set B0 to Low
    
    while(1)
    {
		_delay_ms(500);
		PORTB = 0b00000001;
		_delay_ms(500);
		PORTB = 0b00000000;
	}
}
		
	//TCCR1B |= 1<<CS10  | 1<<CS11 | 0<<CS12; //set Prescaler	
		//if(TCNT1>2232){ //2232=65536/7
		  //  TCNT1=0; //reset counter
		    //PORTB ^= 1<<PINB0; //toggle LED
		//}
    //TODO:: Please write your application code 
