/*
 * MaguireInTheMiddleCode.c
 *
 * Created: 01/02/2023 10:48:39 PM
 * Author : Ishrak
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "def.h"
#include "paddle.h"
#include "joystick.h"
#include "UART.h"
#include "collisions.h"

unsigned char matrix[MAT_ROW][MAT_COL];
struct Ball ball;
struct Maguire maguire;
int playerScores[PLAYER_NUMBER];
volatile int overflowCount;
int gameState;
/*
	0 --> initial state
	1 --> player 1 playing
	2 --> between player 1 and 2
	3 --> player 2 playing
	...
	10 --> game ended 
	
	currPlayer = (gameState>>1)
*/

ISR(TIMER1_OVF_vect)
{
	overflowCount++;
	if(overflowCount==458) // 30 seconds
	{
		if (gameState&1) {
			// time up for the current player
			gameState++;
		}
		overflowCount = 0;
		
	}
}

/*
void takeButtonInput() {
	unsigned char in;
	while (1) {
		in = PIND;
		if(in & 4)
		{
			if (!(gameState&1) && gameState < 10) {
				gameState++;
				uart_send('a');
				_delay_ms(200);
				TCNT1 = 0;
				overflowCount = 0;
				return;
			}			             			
		}
	}
}
*/

ISR(INT0_vect)//STEP2
{
	if (!(gameState&1) && gameState < 10) {
		gameState++;
		uart_send('a');
		TCNT1 = 0;
		overflowCount = 0;
	}
}

void displaytMatrix() {
	/*
		currently written for single color
		will adjust for bi color later
	*/
	int i, j;
	for (i = 0; i < MAT_ROW; i++) {
		// make this row 1
		PORTB = i;
		for (j = 0; j < MAT_COL; j++) {
			if (matrix[i][j]) {
				// make this column 0 (common anode)
				PORTD = (j<<PORTD3);
				if (matrix[i][j] == BALL_MARK || matrix[i][j] == PADDLE_MARK) {
					// set MUX selection bit to 1
					// green
					PORTC |= (1<<PORTC4);
				}
				else {
					// set MUX selection bit to 0
					// red
					PORTC &= ~(1<<PORTC4);
				}
			}
			else {
				// disable both decoders to set all 1 for this column
				PORTD = (1<<PORTD7);
			}
		}
	}
}

/* assigned to Ishrak */
void moveBall() {
	if ((ball.x == 0 && ball.dx < 0) || (ball.x == MAT_ROW-1 && ball.dx > 0)) {
		// hit the top/bottom wall
		// reflect
		ball.dx = -ball.dx;
	}
	if ((ball.y == 0 && ball.dy < 0) || (ball.y == MAT_COL-1 && ball.dy > 0)) {
		// hit the left/right wall
		// reflect
		ball.dy = -ball.dy;
	}
	
	handlePaddleCollisions();
	int maguireCollision = handleMaguireCollisions();
	if (maguireCollision) {
		playerScores[(gameState>>1)]++;
		uart_send('s');
	}
	
	matrix[ball.x][ball.y] = 0;
	
	ball.x += ball.dx;
	if (ball.x < 0) ball.x = 0;
	if (ball.x >= MAT_ROW) ball.x = MAT_ROW-1;
	
	ball.y += ball.dy;
	if (ball.y < 0) ball.y = 0;
	if (ball.y >= MAT_COL) ball.y = MAT_COL-1;
	
	matrix[ball.x][ball.y] = BALL_MARK;	
}

/* assigned to Ishrak */
void moveMaguire(int dx, int dy) {
	/* 
		move along the direction 
		dx displacement along x-axis
		dy displacement along y-axis
	*/
	if ((maguire.x + dx < 0) || (maguire.x + MAG_SIZE-1 + dx >= MAT_ROW)) {
		// hit the top/bottom wall
		dx = 0;
	}
	if ((maguire.y + dy < 0) || (maguire.y + MAG_SIZE-1 + dy >= MAT_COL)) {
		// hit the left/right wall
		dy = 0;
	}
	
	// check if maguire collides with paddle
	for (int i = 0; i < MAG_SIZE; i++) {
		for (int j = 0; j < MAG_SIZE; j++) {
			if (matrix[maguire.x+dx+i][maguire.y+dy+j] == PADDLE_MARK) {
				dx = dy = 0;
				break;
			} 
		}
	}
	
	for (int i = 0; i < MAG_SIZE; i++) {
		for (int j = 0; j < MAG_SIZE; j++) {
			matrix[maguire.x+i][maguire.y+j] = 0;
		}
	}
	
	maguire.x += dx;
	maguire.y += dy;
	
	for (int i = 0; i < MAG_SIZE; i++) {
		for (int j = 0; j < MAG_SIZE; j++) {
			matrix[maguire.x+i][maguire.y+j] = MAGUIRE_MARK;
		}
	}
}

// initialize ball
void initBall() {
	ball.dx = BALL_SPEED;
	ball.dy = BALL_SPEED;
	ball.x = 2;
	ball.y = 3;
	matrix[ball.x][ball.y] = BALL_MARK;
}

// initialize ball
void initMaguire() {
	maguire.x = 3;
	maguire.y = 8;
	for (int i = 0; i < MAG_SIZE; i++) {
		for (int j = 0; j < MAG_SIZE; j++) {
			matrix[maguire.x+i][maguire.y+j] = MAGUIRE_MARK;
		}
	}
}

void initTimer() {
	overflowCount = 0;
	//configure timer
	TCCR1A = 0b00000000; // normal mode
	TCCR1B = 0b00000001; // no prescaler, internal clock
	TIMSK = 0b00000100; //Enable Overflow Interrupt
}

void initButtonInterrupt() {
	GICR = (1 << INT0); //STEP3
	MCUCR = MCUCR | (1 << ISC01);//STEP4
	MCUCR = MCUCR | (1 << ISC00);//STEP4
}

void initGame() {
	gameState = 0;
}

/* initialize all ports */
void init() {
	DDRB = 0xFF; // matrix row
	/*
		matrix row from B0-B3
		B0-B2 : Decoder input bits
		B3 : Extension between two active-high decoders
	*/
	DDRD = 0xFF; 
	/*
		matrix column from D3-D7
		D3-D5 : Decoder input bits
		D6 : Extension between two active-low decoders
		D7 : For setting off all column values
	*/
	DDRC = 0xFF; 
	/*
		C2 : Joystick x-direction selection
		C3 : Joystick y-direction selection
		C4 : Red/green selection 
				0 --> red
				1 --> green
	*/
	
	// TODO: set up other ports
	uart_init();
	_delay_ms(1000);
	
	init_paddle();
	
	initBall();
	initMaguire();
	initGame();
	initButtonInterrupt();
	initTimer();
	sei(); //Global Interrupt Enable
}

/* assigned to Ishrak */
/*
void takeGyroscopeInput() {
	uart_send('g');
	_delay_ms(10);
	for (int i = 0; i < 20; i++) {
		displaytMatrix();
	}
	unsigned char dxr = uart_receive();
	for (int i = 0; i < 20; i++) {
		displaytMatrix();
	}
	//_delay_ms(200);
	unsigned char dyr = uart_receive();
	for (int i = 0; i < 20; i++) {
		displaytMatrix();
	}
	//_delay_ms(200);
	int dx = dxr;
	int dy = dyr;
	moveMaguire(dx-5, dy-5);
	//uart_send('f');
	//_delay_ms(200);
}
*/

int main(void)
{
    /* Replace with your application code */
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);

	init();
    while (1) 
    {
		if (gameState&1) {
			for (int i = 0; i < 20; i++) {
				displaytMatrix();
			}
			if (!(gameState&1)) continue;
			moveBall();
			for (int i = 0; i < 10; i++) {
				displaytMatrix();
			}
			uart_send('g'); // want to take gyroscope input
			if (!(gameState&1)) continue;
			for (int i = 0; i < 2; i++) {
				PORTC = (i<<2);
				takeJoystickInput(i);
			}
			if (!(gameState&1)) continue;
		
			for (int i = 0; i < 10; i++) {
				displaytMatrix();
			}
			unsigned char dxr = 5, dyr = 5;
			if (!(gameState&1)) continue;
			dxr = uart_receive();
			if (!(gameState&1)) continue;
			for (int i = 0; i < 10; i++) {
				displaytMatrix();
			}
			if (!(gameState&1)) continue;
			for (int i = 2; i < 4; i++) {
				PORTC = (i<<2);
				takeJoystickInput(i);
			}
		
			for (int i = 0; i < 10; i++) {
				displaytMatrix();
			}
			if (!(gameState&1)) continue;
			dyr = uart_receive();
			if (!(gameState&1)) continue;
			for (int i = 0; i < 10; i++) {
				displaytMatrix();
			}
			
			int dx = dxr;
			int dy = dyr;
			if (!(gameState&1)) continue;
			moveMaguire(dx-5, dy-5);
		}
		else {
			for (int i = 0; i < 20; i++) {
				displaytMatrix();
			}
		}
    }
}

