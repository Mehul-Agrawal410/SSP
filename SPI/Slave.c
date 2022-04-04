/*
 * SPI2.c
 *
 * Created: 28-03-2022 22:01:03
 * Author : Mehul
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#define BAUD_RATE ((F_CPU/(4800*16UL))-1)
#include <util/delay.h>

void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);
void SPI_SlaveTransmit(char data);

void USART_Init(void);
char USART_Receive(void);
void USART_Transmit(char cdata);



int main(void)
{
	SPI_SlaveInit();
	//USART_Init();
	//DDRA = 0xFF;
	//PORTA = 0x00;
	PORTD = SPI_SlaveReceive();
	_delay_ms(100);
	SPI_SlaveTransmit(0x03);
	_delay_ms(100);
    while (1) 
    {
		//char a = SPI_SlaveReceive();
		//USART_Transmit(a);
		//char b = USART_Receive();
		//_delay_ms(100);
		//PORTD = SPI_SlaveReceive();
		//_delay_ms(100);
		//SPI_SlaveTransmit(0x03);
		//_delay_ms(100);
    }
}

void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDRB = (1<<DDB3);
	/* Enable SPI */
	SPCR = (1<<SPE);
}

void SPI_SlaveTransmit(char data)
{
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));
}

char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	return SPDR;
}

void USART_Init(void){
	UCSR0B = 1<<TXEN0 | 1<<RXEN0;
	UCSR0C = 0x06; 
	UBRR0H = BAUD_RATE>>8;
	UBRR0L = BAUD_RATE;
}
void USART_Transmit(char cdata){
	while(!(UCSR0A & 1<<UDRE0));
	UDR0 = cdata;
}
char USART_Receive(void){
	while(!(UCSR0A&(1<<RXC0)));
	return UDR0;	
}

