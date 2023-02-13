/*
 * collisions.h
 *
 * Created: 06/02/2023 12:58:00 PM
 *  Author: Ishrak
 */ 


#ifndef COLLISIONS_H_
#define COLLISIONS_H_

#include "def.h"

extern struct Ball ball;
extern struct Maguire maguire;

void handleBottomPaddleCollision() {
	// handle if ball comes from top
	// ball.x+ball.dx matches paddles[DOWN].x
	int dif = ball.y + ball.dy - paddles[DOWN].y; 
	if (dif == 0) {
		ball.dx = -1;
		ball.dy = -1;
	}
	else if (dif == 1) {
		ball.dx = -1;
		ball.dy = -1;
	}
	else if (dif == 2) {
		ball.dx = -ball.dx;
	}
	else if (dif == 3) {
		ball.dx = -1;
		ball.dy = 1; 
	}
	else if (dif == 4) {
		ball.dx = -1;
		ball.dy = 1;
	}
}

void handleTopPaddleCollision() {
	// handle if ball comes from bottom
	// ball.x+ball.dx matches paddles[UP].x
	int dif = ball.y + ball.dy - paddles[UP].y;
	if (dif == 0) {
		ball.dx = -1;
		ball.dy = 1;
	}
	else if (dif == 1) {
		ball.dx = -1;
		ball.dy = 1;
	}
	else if (dif == 2) {
		ball.dx = -ball.dx;
	}
	else if (dif == 3) {
		ball.dx = 1;
		ball.dy = 1;
	}
	else if (dif == 4) {
		ball.dx = 1;
		ball.dy = 1;
	}
}

void handleRightPaddleCollision() {
	// handle if ball comes from left
	// ball.y+ball.dy matches paddles[RIGHT].y
	int dif = ball.x + ball.dx - paddles[RIGHT].x;
	if (dif == 0) {
		ball.dx = -1;
		ball.dy = -1;
	}
	else if (dif == 1) {
		ball.dx = -1;
		ball.dy = -1;
	}
	else if (dif == 2) {
		ball.dy = -ball.dy;
	}
	else if (dif == 3) {
		ball.dx = 1;
		ball.dy = -1;
	}
	else if (dif == 4) {
		ball.dx = 1;
		ball.dy = -1;
	}
}

void handleLeftPaddleCollision() {
	// handle if ball comes from left
	// ball.y+ball.dy matches paddles[LEFT].y
	int dif = ball.x + ball.dx - paddles[LEFT].x;
	if (dif == 0) {
		ball.dx = -1;
		ball.dy = 1;
	}
	else if (dif == 1) {
		ball.dx = -1;
		ball.dy = 1;
	}
	else if (dif == 2) {
		ball.dy = -ball.dy;
	}
	else if (dif == 3) {
		ball.dx = 1;
		ball.dy = 1;
	}
	else if (dif == 4) {
		ball.dx = 1;
		ball.dy = 1;
	}
}

void handleBottomMaguireCollision() {
	// handle if ball comes from bottom
	int dif = ball.y + ball.dy - maguire.y;
	if (dif == -1) {
		ball.dx = 1;
		ball.dy = -1;
	}
	else if (dif == 0) {
		ball.dx = 1;
		ball.dy = -1;
	}
	else if (dif == 1) {
		ball.dx = 1;
		ball.dy = 1;
	}
	else if (dif == 2) {
		ball.dx = 1;
		ball.dy = 1;
	}
}

void handleTopMaguireCollision() {
	// handle if ball comes from top
	int dif = ball.y + ball.dy - maguire.y;
	if (dif == -1) {
		ball.dx = -1;
		ball.dy = -1;
	}
	else if (dif == 0) {
		ball.dx = -1;
		ball.dy = -1;
	}
	else if (dif == 1) {
		ball.dx = -1;
		ball.dy = 1;
	}
	else if (dif == 2) {
		ball.dx = -1;
		ball.dy = 1;
	}
}

void handleLeftMaguireCollision() {
	// handle if ball comes from left
	int dif = ball.x + ball.dx - maguire.x;
	if (dif == 0) {
		ball.dx = 1;
		ball.dy = -1;
	}
	else if (dif == 1) {
		ball.dx = -1;
		ball.dy = -1;
	}
}

void handleRightMaguireCollision() {
	// handle if ball comes from right
	int dif = ball.x + ball.dx - maguire.x;
	if (dif == 0) {
		ball.dx = 1;
		ball.dy = 1;
	}
	else if (dif == 1) {
		ball.dx = -1;
		ball.dy = 1;
	}
}

void handlePaddleCollisions() {
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
}

int handleMaguireCollisions() {
	// handle ball collision with maguire
	int flag = 0;
	// bottom surface
	if (ball.x-1 == maguire.x && ball.y >= maguire.y-1 && ball.y <= maguire.y+MAG_SIZE) {
		handleBottomMaguireCollision();
		flag = 1;
	}
	// top surface
	else if (ball.x == maguire.x-MAG_SIZE && ball.y >= maguire.y-1 && ball.y <= maguire.y+MAG_SIZE) {
		handleTopMaguireCollision();
		flag = 1;
	}
	// right surface
	else if (ball.y == maguire.y+MAG_SIZE && ball.x >= maguire.x && ball.x < maguire.x-MAG_SIZE) {
		handleRightMaguireCollision();
		flag = 1;
	}
	// left surface
	else if (ball.y+1 == maguire.y && ball.x >= maguire.x && ball.x < maguire.x-MAG_SIZE) {
		handleLeftMaguireCollision();
		flag = 1;
	}
	return flag;
}


#endif /* COLLISIONS_H_ */