/*
 * USART.c
 *
 * Created: 25-03-2022 20:45:55
 * Author : Mehul
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#define USART_BAUDRATE 4800
#define BAUD_PRESCALE ((F_CPU/(USART_BAUDRATE*16UL))-1)

char usart_getch();
void Config_USART();

int main(void)
{
	DDRB = 0b00000001;
	PORTB = 0x00;
	int i = 0;
	unsigned char data[] = "Press 1 to turn on the LED \r\n";
	Config_USART();
	while (1)
	{
		while (data[i] != 0)
		{
			while(!(UCSR0A & (1<<UDRE0)));
			UDR0 = data[i];
			i++;
		}
		char a = usart_getch();
		char b = '1';
		if (a == b)
		{
			PORTB = 0xFF;
		}
		else
		{
			PORTB = 0x00;
		}
	}
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

char usart_getch()
{
	while (!(UCSR0A & (1 << RXC0)));
	// Do nothing until data has been received and is ready to be read from UDR
	return(UDR0); // return the byte
}

