/*
 * SPI1.c
 *
 * Created: 28-03-2022 22:24:07
 * Author : Mehul
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#define BAUD_RATE ((F_CPU/(4800*16UL))-1)
#include <util/delay.h>

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
char SPI_MasterReceive();

void USART_Init(void);
void USART_Transmit(char data);
char USART_Receive(void);




int main(void)
{
	SPI_MasterInit();
	//USART_Init();
	
	SPI_MasterTransmit(0x07);
	_delay_ms(100);
	PORTF = SPI_MasterReceive();
	_delay_ms(100);

    while (1) 
    {
		//char a  = USART_Receive();
		
		//USART_Transmit(b);
    }
}

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransmit(char cData)
{
	 //Start transmission 
	SPDR = cData;
	 //Wait for transmission complete 
	while(!(SPSR & (1<<SPIF)))
	;
}

char SPI_MasterReceive(void)
{
	SPDR = 0x07;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}

void USART_Init(){
	UBRR0H = BAUD_RATE>>8;
	UBRR0L = BAUD_RATE;
	UCSR0B = 1<<RXEN0 | 1<<TXEN0;
	UCSR0C = 0x06;
}
void USART_Transmit(char data){
	while(!(UCSR0A&(1<<UDRE0)));
	SPDR = data;
}
char USART_Receive(){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}




