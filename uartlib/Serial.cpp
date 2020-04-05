/*
 * Serialial.cpp
 *
 * Created: 05-04-2020 14:06:12
 *  Author: nishanchettri
 *	Email: nishanchettri@gmail.com
 */ 

#include "uart.h"
#include <avr/io.h>

void Serial:: begin(uint32_t baud,uint8_t frequency_mhz)
{
	DDRD|=(1<<PIND1);//SET TX PIN AS OUTPUT
	UCSRB|=(1<<RXEN)|(1<<TXEN);//ENABLE RX AND TX
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);//SET DATA SIZE TO 8 BIT AND ENABLE UCSRC
	UBRRL= ((frequency_mhz*1000000)/(baud*16))-1; // SETTING BAUD RATE 	
}	

void Serial:: send(char buff[])
{

	for(int i=0;i<strlen(buff);i++)
	{
		UDR=buff[i]; //PUT VALUE INTO DATA REGISTER
		while(!(UCSRA&(1<<UDRE)));//WAIT UNTILL THE DATA REGISTER IS EMPTY
	}
}
int Serial:: available()
{
	//IF SOMETHING RECEIVED THEN TRUE ELSE FALSE
	if(UCSRA&(1<<RXC))
	return UDR;
	
	else
	return 0;
}
int Serial::receive(char *ptr_string)
{
	uint8_t len = 0;
	while(1)
	{
		while(!(UCSRA&(1<<RXC)));//WAIT TILL SOMETHING IS RECEIVED
		char ch=UDR;
		if((ch=='\r') || (ch=='\n')) //read till enter key is pressed
		{						     //once enter key is pressed null terminate the string
			ptr_string[len]=0;           //and break the loop
			break;
		}
		else if((ch=='\b') && (len!=0))
		{
			len--;    //If backspace is pressed then decrement the index to remove the old char
		}
		else
		{
			ptr_string[len]=ch; //copy the char into string and increment the index
			len++;
		}
	}
	return len;
}

bool Serial::sent()
{
	//IF ANY DATA SENT THEN TRUE ELSE FALSE
	if(UCSRA&(1<<TXC))
	return true;
	else
	return false;
}