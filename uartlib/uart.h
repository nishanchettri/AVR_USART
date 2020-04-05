/*
 * uart.h
 *
 * Created: 05-04-2020 14:44:23
 *  Author: nisha
 */ 


#ifndef uart_H_
#define uart_H_
#include <string.h>
#include <stdint.h>

class Serial
{
	public:
	//FUNCTION PROTOTYPES
	void begin(uint32_t baud,uint8_t);
	static void send(char buff[]);
	int available();
	int receive(char *ptr_string);
	bool sent();
	
	
};





#endif /* UART_H_ */