/*
 * UART.h
 *
 * Created: 04/02/2023 01:46:59 PM
 *  Author: Ishrak
 */ 


#ifndef UART_H_
#define UART_H_

void uart_init()
{
	UCSRA = 0b00000010;
	UCSRB = 0b00011000;
	UCSRC = 0b10000110;
	UBRRH = 0;
	UBRRL = 12;
}
void uart_send(unsigned char data){
	while ((UCSRA & (1<<UDRE)) == 0x00);
	UDR = data;
}
unsigned char uart_receive(void){
	while ((UCSRA & (1<<RXC)) == 0x00);
	return UDR;
}

#endif /* UART_H_ */