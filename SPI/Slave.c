/*
 * SPI2.c
 *
 * Created: 28-03-2022 22:01:03
 * Author : Mehul
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);
void SPI_SlaveTransmit(char data);

uint8_t i = 0x00;

int main(void)
{
	SPI_SlaveInit();
    while (1) 
    {
		PORTA = SPI_SlaveReceive();
		SPI_SlaveTransmit(i++);
		_delay_ms(1000);
    }
}

void SPI_SlaveInit(void)
{
	DDRB = (1<<DDB3);
	SPCR = (1<<SPE);
}

void SPI_SlaveTransmit(char data)
{
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));
}

char SPI_SlaveReceive(void)
{
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

