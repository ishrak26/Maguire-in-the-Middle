#pragma once

#define MAT_ROW 16
#define MAT_COL 16

#define MAG_SIZE 2

#define BALL_SPEED 1

#define PADDLE_LEN 5
#define MAX_PADDLE_MOVEMENT 2


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

#define JOYSTICK_THRESHOLD 150
#define JOYSTICK_SENSITIVITY 100

struct Ball {
	/*
		(x, y) is the coordinates of the ball
		(dx, dy) is the displacement along x and y-axis per unit time
	*/
	int x, y;
	int dx, dy;		
};

struct Maguire {
	/*
		(x, y) is the bottom-left coordinate of the Maguire
	*/
	int x, y;
};



