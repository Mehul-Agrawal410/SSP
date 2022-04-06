/*
 * SPI1.c
 *
 * Created: 28-03-2022 22:24:07
 * Author : Mehul
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
char SPI_MasterReceive();

uint8_t i = 0x00;

int main(void)
{
	SPI_MasterInit();
    while (1) 
    {
		SPI_MasterTransmit(i++);
		PORTF = SPI_MasterReceive();
		_delay_ms(1000);
    }
}

void SPI_MasterInit(void)
{
	DDRB = (1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransmit(char cData)
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF)))
	;
}

char SPI_MasterReceive(void)
{
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}




