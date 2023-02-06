/*
 * collisions.h
 *
 * Created: 06/02/2023 12:58:00 PM
 *  Author: Ishrak
 */ 


#ifndef COLLISIONS_H_
#define COLLISIONS_H_

extern struct Ball ball;

void handleBottomPaddleCollision() {
	// handle if ball comes from top
	// ball.x+ball.dx matches paddles[DOWN].x
	int dif = ball.y + ball.dy - paddles[DOWN].y; 
	if (dif == 0) {
		
	}
	else if (dif == 1) {
		
	}
	else if (dif == 2) {
		ball.dx = -ball.dx;
	}
	else if (dif == 3) {
		
	}
	else if (dif == 4) {
		
	}
}


#endif /* COLLISIONS_H_ */