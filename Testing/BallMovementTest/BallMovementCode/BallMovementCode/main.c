/*
 * MaguireInTheMiddleCode.c
 *
 * Created: 01/02/2023 10:48:39 PM
 * Author : User
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

#define MAT_ROW 16
#define MAT_COL 16
#define PADDLE_LEN 4
#define MAG_SIZE 2

#define BALL_SPEED 1

/* 
	directions 
	corresponding bit will be set
	other bits will be reset
*/
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
/*
	for up and right, direction will be 0b0011
	for down and left, direction will be 0b1100 and so on
	for setting up, direction |= (1<<UP);
	for setting left, direction |= (1<<LEFT); and so on
	
	initially assign 0 to direction, and then set what's needed
*/

struct Ball {
	/*
		(x, y) is the coordinates of the ball
		(dx, dy) is the displacement along x and y-axis per unit time
	*/
	int x, y;
	int dx, dy;		
} ball;

struct Paddle {
	/*
		(x, y) is the leftmost coordinate of the paddle
	*/
	int x, y;
} paddles[4];
/*
	paddle indices are given as follows:
	top --> 0
	right --> 1
	bottom --> 2
	left --> 3
*/

struct Maguire {
	/*
		(x, y) is the bottom-left coordinate of the Maguire
	*/
	int x, y;
} maguire;

unsigned char matrix[16][16];

void displaytMatrix() {
	/*
		currently written for single color
		will adjust for bi color later
	*/
	int i, j;
	for (i = 0; i < MAT_COL; i++) {
		PORTD = i;
		for (j = 0; j < MAT_ROW; j++) {
			if (matrix[j][i]) {
				// make row 0 (common cathode)
				PORTB = j;
			}
			else {
				PORTB = 16;
			}
			_delay_ms(1);
		}
		
	}
}

/* assigned to Ishrak */
void moveBall() {
	if ((ball.x == 0 && ball.dx == -1) || (ball.x == MAT_ROW-1 && ball.dx == 1)) {
		// hit the top/bottom wall
		// reflect
		ball.dx = -ball.dx;
	}
	if ((ball.y == 0 && ball.dy == -1) || (ball.y == MAT_COL-1 && ball.dy == 1)) {
		// hit the left/right wall
		// reflect
		ball.dy = -ball.dy;
	}
	
	matrix[ball.x][ball.y] = 0;
	ball.x += ball.dx;
	ball.y += ball.dy;
	matrix[ball.x][ball.y] = 1;
	
}

/* assigned to Anonto */
void movePaddle(int direction, int idx) {
	/* move paddle[idx] 1 unit along the direction */ 
}

/* assigned to Ishrak */
void moveMaguire(int dx, int dy) {
	/* 
		move along the direction 
		dx displacement along x-axis
		dy displacement along y-axis
	*/
	
}

/* assigned to Farhan, Akash */
void takeJoystickInput() {
	/*
		just take the current joystick input
		joystick MUX selection bit will be handled by the caller 
	*/
}

/* assigned to Saffat, Farhan */
void takeGyroscopeInput() {
	
}

/* assigned to Akash */
void playMusic() {
	
}

/* assigned to TBA */
void displayLCD() {
	
}

/* all collisions/interceptions and gameplay logic will be handled later */

/* initialize all ports */
void init() {
	DDRB = 0xFF; // matrix row
	DDRD = 0xFF; // matrix column

	ball.dx = BALL_SPEED;
	ball.dy = BALL_SPEED;
	ball.x = 2;
	ball.y = 3;
	matrix[ball.x][ball.y] = 1;
	// TODO: set up other ports
}

int main(void)
{
    /* Replace with your application code */
	init();
    while (1) 
    {
		
		displaytMatrix();
		moveBall();
		_delay_ms(200);
    }
}

