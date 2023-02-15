#pragma once
/* assigned to Farhan, Akash */

#include "def.h"
#include "paddle.h"
#include "UART.h"

void takeJoystickInput(int idx) {
	/*
		just take the current joystick input
		joystick MUX selection bit will be handled by the caller 
	*/
	unsigned char horizontalmov, verticalmov;
	int direction = 0;
	
	ADMUX = 0b01100000; //setting the reference of ADC
	ADCSRA = 0b10000010; //enabling the ADC, setting pre-scalar 4

	ADCSRA |= (1<<ADSC); //start ADC conversion
	while (ADCSRA & (1<<ADSC)); //wait till ADC conversion
	
	horizontalmov = ADCH; //moving value
	
	ADMUX |= 1; //changing channel			

	ADCSRA |= (1<<ADSC);// start ADC conversion
	while (ADCSRA & (1<<ADSC));// wait till ADC conversion
	verticalmov = ADCH;// moving value
				
	if (horizontalmov < JOYSTICK_THRESHOLD-JOYSTICK_SENSITIVITY)
	{
		direction |= (1<<LEFT);
	}
	else if (horizontalmov > JOYSTICK_THRESHOLD+JOYSTICK_SENSITIVITY)
	{
		direction |= (1<<RIGHT);
	}
	
	if (verticalmov < JOYSTICK_THRESHOLD-JOYSTICK_SENSITIVITY)
	{
		direction |= (1<<UP);
	}
	else if (verticalmov > JOYSTICK_THRESHOLD+JOYSTICK_SENSITIVITY)
	{
		direction |= (1<<DOWN);
	}
	//uart_send(horizontalmov);
	//_delay_ms(1000);
	//uart_send(verticalmov);
	//_delay_ms(1000);

	movePaddle(direction, idx);
}