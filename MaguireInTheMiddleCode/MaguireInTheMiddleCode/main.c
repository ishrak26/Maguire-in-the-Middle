/*
 * MaguireInTheMiddleCode.c
 *
 * Created: 01/02/2023 10:48:39 PM
 * Author : Ishrak
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

#include "def.h"
#include "paddle.h"
#include "joystick.h"
#include "UART.h"
#include "collisions.h"

unsigned char matrix[MAT_ROW][MAT_COL];
struct Ball ball;
struct Maguire maguire;

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
				PORTD = (j<<2);
			}
			else {
				// disable both decoders to set all 1 for this column
				PORTD = 64;
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
	
	// handle ball collision with paddle
	// bottom paddle
	if (ball.x+1 == paddles[DOWN].x && ball.y >= paddles[DOWN].y && ball.y < paddles[DOWN].y+PADDLE_LEN) {
		handleBottomPaddleCollision();
	}
	// top paddle
	else if (ball.x-1 == paddles[UP].x && ball.y >= paddles[UP].y && ball.y < paddles[UP].y+PADDLE_LEN) {
		handleTopPaddleCollision();
	}
	// right paddle
	else if (ball.y+1 == paddles[RIGHT].y && ball.x >= paddles[RIGHT].x && ball.x < paddles[RIGHT].x+PADDLE_LEN) {
		handleRightPaddleCollision();
	}
	// left paddle
	else if (ball.y-1 == paddles[LEFT].y && ball.x >= paddles[LEFT].x && ball.x < paddles[LEFT].x+PADDLE_LEN) {
		handleLeftPaddleCollision();
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

/* assigned to Akash */
void playMusic() {
	
}

/* assigned to TBA */
void displayLCD() {
	
}

/* all collisions/interceptions and gameplay logic will be handled later */

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

/* initialize all ports */
void init() {
	DDRB = 0xFF; // matrix row
	DDRD = 0xFF; // matrix column
	DDRC = 0xFF; // analog mux (joystick) selection bits
	// TODO: set up other ports
	uart_init();
	_delay_ms(1000);
	
	init_paddle();
	//
	initBall();
	initMaguire();
}

/* assigned to Ishrak */
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


int main(void)
{
    /* Replace with your application code */
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);

	init();
    while (1) 
    {
		for (int i = 0; i < 20; i++) {
			displaytMatrix();
		}
		moveBall();
		uart_send('g');
		
		for (int i = 0; i < 2; i++) {
			PORTC = (i<<2);
			takeJoystickInput(i);
		}
		for (int i = 0; i < 10; i++) {
			displaytMatrix();
		}
		unsigned char dxr = uart_receive();
		
		for (int i = 2; i < 4; i++) {
			PORTC = (i<<2);
			takeJoystickInput(i);
		}
		for (int i = 0; i < 10; i++) {
			displaytMatrix();
		}
		unsigned char dyr = uart_receive();
		for (int i = 0; i < 20; i++) {
			displaytMatrix();
		}
		int dx = dxr;
		int dy = dyr;
		moveMaguire(dx-5, dy-5);
    }
}

