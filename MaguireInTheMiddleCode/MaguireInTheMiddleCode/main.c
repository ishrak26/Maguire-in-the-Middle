/*
 * MaguireInTheMiddleCode.c
 *
 * Created: 01/02/2023 10:48:39 PM
 * Author : User
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

#include "def.h"
#include "paddle.h"
#include "joystick.h"
#include "UART.h"

unsigned char matrix[MAT_ROW][MAT_COL];

struct Ball {
	/*
		(x, y) is the coordinates of the ball
		(dx, dy) is the displacement along x and y-axis per unit time
	*/
	int x, y;
	int dx, dy;		
} ball;

struct Maguire {
	/*
		(x, y) is the bottom-left coordinate of the Maguire
	*/
	int x, y;
} maguire;

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
	
	matrix[ball.x][ball.y] = 0;
	ball.x += ball.dx;
	ball.y += ball.dy;
	matrix[ball.x][ball.y] = 1;	
}

/* assigned to Ishrak */
void moveMaguire(int dx, int dy) {
	/* 
		move along the direction 
		dx displacement along x-axis
		dy displacement along y-axis
	*/
	if ((maguire.x == 0 && dx == -1) || (maguire.x+MAG_SIZE == MAT_ROW && dx == 1)) {
		// hit the top/bottom wall
		dx = 0;
	}
	if ((maguire.y == 0 && dy == -1) || (maguire.y+MAG_SIZE == MAT_COL && dy == 1)) {
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
			matrix[maguire.x+i][maguire.y+j] = 1;
		}
	}
}

/* assigned to Saffat, Farhan */
void takeGyroscopeInput() {
	uart_send('g');
	_delay_ms(200);
	int dx = uart_receive();
	int dy = uart_receive();
	moveMaguire(dx, dy);
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
	matrix[ball.x][ball.y] = 1;
}

// initialize ball
void initMaguire() {
	maguire.x = 2;
	maguire.y = 3;
	for (int i = 0; i < MAG_SIZE; i++) {
		for (int j = 0; j < MAG_SIZE; j++) {
			matrix[maguire.x+i][maguire.y+j] = 1;
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
	
	initBall();
	//initMaguire();
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
		//moveBall();
		//for (int i = 0; i < 4; i++) {
			//PORTC = (i<<2);
			//takeJoystickInput(i);
		//}
		takeGyroscopeInput();
		
    }
}

