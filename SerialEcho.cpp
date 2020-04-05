/*
 * usart.cpp
 *
 * Created: 05-04-2020 14:51:59
 *  Author: nishan chettri
	Email: nishanchettri@gmail.com
	Website: nishanchettri.com
 */ 


#include "uart.h"

Serial ser;

char word[50];

int main(void)
{
   
   ser.begin(9600,12); //baud rate, crystal frequency

   while(1)
   {
	   if(ser.available()>0)
	   {
		   ser.receive(word);
		   ser.send(word);
	   }

   }
}