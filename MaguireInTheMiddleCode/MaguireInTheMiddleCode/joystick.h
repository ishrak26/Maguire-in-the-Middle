/* assigned to Farhan, Akash */
#pragma once
#include "def.h"
#include "Paddle.h"


int takeJoystickInput(int idx) {
	/*
		just take the current joystick input
		joystick MUX selection bit will be handled by the caller 
	*/
	int HORIZONTALMOV = 0;
	int VERTICAlMOV = 0;
	int direction = 0b00000000;
	unsigned int adcl, adch, adc;
	ADMUX = 0b01100000; //setting the reference of ADC
	ADCSRA |= (1<<ADEN)|(1<<ADPS0); //enabling the ADC, setting pre-scalar 2

	ADCSRA |= (1<<ADSC);//start ADC conversion
	while ( !(ADCSRA & (1<<ADSC)));//wait till ADC conversion
	adcl = ADCL;
	adch = ADCH;
	adc = (adch<<2) | (adcl>>6);
	HORIZONTALMOV = adc;//moving value
	ADC=0;//reset ADC register
	ADMUX=0b01100001;//changing channel
	//break;			

	ADCSRA |= (1<<ADSC);// start ADC conversion
	while ( !(ADCSRA & (1<<ADSC)));// wait till ADC conversion
	adcl = ADCL;
	adch = ADCH;
	adc = (adch<<2) | (adcl>>6);
	VERTICAlMOV = adc;// moving value
	ADC=0;// reset ADC register
	//ADMUX=0b01100000;// changing channel
	//break;
				
	if (HORIZONTALMOV < JOYSTICK_THRESHOLD-150)
	{
		direction |= (1<<LEFT);
	}
	if (HORIZONTALMOV > JOYSTICK_THRESHOLD+150)
	{
		direction | = (1<<RIGHT);
	}
	if (VERTICAlMOV < JOYSTICK_THRESHOLD-150)
	{
		direction | = (1<<DOWN);
	}
	if (VERTICAlMOV > JOYSTICK_THRESHOLD+150)
	{
		direction | = (1<<UP);
	}

	movePaddle(direction, idx);
}