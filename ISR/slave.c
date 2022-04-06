/*
 * ISR_Slave.c
 *
 * Created: 03-04-2022 19:56:34
 * Author : Mehul
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void Slave_Init(void);

char z;
uint8_t i = 0x01;

ISR(SPI_STC_vect){
	z = SPDR;
	SPDR = i++;
}
 
int main(void)
{
    Slave_Init();
    while (1) 
    {
		PORTD = z;
		_delay_ms(1000);
    }
}

void Slave_Init(){
	sei();
	DDRB = (1<<DDB3);
	SPCR = (1<<SPE) | (1<<SPIE); 
}

