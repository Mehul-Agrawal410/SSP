/*
 * SPI1.c
 *
 * Created: 28-03-2022 22:24:07
 * Author : Mehul
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define USART_BAUDRATE 4800
#define BAUD_PRESCALE ((F_CPU/(USART_BAUDRATE*16UL))-1)

void Config_USART();
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
char SPI_MasterReceive();

uint8_t i = 0x00;

int main(void)
{
	SPI_MasterInit();
	Config_USART();
    while (1) 
    {
		SPI_MasterTransmit(i++);
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = SPI_MasterReceive();
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

void Config_USART(){
	UBRR0H = (BAUD_PRESCALE>>8);
	UBRR0L = BAUD_PRESCALE;
	//Enable receiver and transmitter
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	//Set frame format: 8data, 2stop bit
	UCSR0C = 0x06;
	//UCSR0C = (1<<USBS0)|(3<<UCSZ0);
}
