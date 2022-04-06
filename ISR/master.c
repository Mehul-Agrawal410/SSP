/*
 * ISR_Master.c
 *
 * Created: 03-04-2022 19:21:15
 * Author : Mehul
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void Master_Init(void);

char y;
uint8_t i = 0x01;

ISR(SPI_STC_vect){
	y = SPDR; 
}

int main(void)
{ 
	Master_Init();
    while (1) 
    {
		SPDR = i++;
		PORTF = y;
		_delay_ms(1000);
    }
}

void Master_Init(void){
	sei();
	DDRB = (1<<DDB1) | (1<<DDB2) | (1<<DDB0);
	SPCR = (1<<SPE) | (1<<SPIE) | (1<<MSTR) | (1<<SPR0);
}
