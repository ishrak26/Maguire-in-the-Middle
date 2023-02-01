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

/* directions */
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

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

unsigned char matrix[MAT_ROW][MAT_COL];

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
				PORTD = j;
			}
			else {
				// disable both decoders to set all 1 for this column
				PORTD = 16;
			}
		}
	}
}

/* assigned to Ishrak */
void moveBall() {
	
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

/* all collisions and gameplay logic will be handled later */

/* initialize all ports */
void init() {
	DDRB = 0xFF; // matrix row
	DDRD = 0xFF; // matrix column
	// TODO: set up other ports
}

int main(void)
{
    /* Replace with your application code */
	init();
    while (1) 
    {
		displaytMatrix();
		for (int i = 0; i < 4; i++) {
			// assign joystick MUX selection bit
			takeJoystickInput();
			displaytMatrix();
		}
		takeGyroscopeInput();
		displaytMatrix();
    }
}

