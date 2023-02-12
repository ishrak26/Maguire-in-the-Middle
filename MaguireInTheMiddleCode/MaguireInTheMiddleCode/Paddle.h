#pragma once

/* assigned to Anonto */
#include "def.h"

extern unsigned char matrix[MAT_ROW][MAT_COL];

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

//initializes the paddle positions

void init_paddle() {
	//top
	paddles[0].x = 0;
	paddles[0].y = 6;
	
	//right
	paddles[1].x = 6;
	paddles[1].y = MAT_COL-1;
	
	//bottom
	paddles[2].x = MAT_ROW-1;
	paddles[2].y = 6;
	
	//left
	paddles[3].x = 6;
	paddles[3].y = 0;
	
	for (int j = 0; j < 4; j += 2) {
		for(int i = 0; i<PADDLE_LEN; i++){
			matrix[paddles[j].x][paddles[j].y+i] = PADDLE_MARK;
		}
	}
	for (int j = 1; j < 4; j += 2) {
		for(int i = 0; i<PADDLE_LEN; i++){
			matrix[paddles[j].x+i][paddles[j].y] = PADDLE_MARK;
		}
	}
	
}

void update_TopPaddle(int direction){
	
	int collision_flag = 0;
	
	//Updating value to zero 
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[0].x][paddles[0].y+i] = 0;
	}
	
	//Up
	if ((direction & (1<<UP)) && paddles[0].x){
		
		       paddles[0].x--;
	}
	//Down
	else if ((direction & (1<<DOWN)) && (paddles[0].x < MAX_PADDLE_MOVEMENT-1)){
		for(int i = 0; i<PADDLE_LEN; i++){
			if(matrix[paddles[0].x+1][paddles[0].y+i] == PADDLE_MARK){
				collision_flag = 1;
			}
		}
		if(!collision_flag){
		     paddles[0].x++;	
		}
	}
	
	//Right
	if ((direction & (1<<RIGHT)) && (paddles[0].y < MAT_COL-PADDLE_LEN) && (matrix[paddles[0].x][paddles[0].y + PADDLE_LEN] != PADDLE_MARK)){
	    paddles[0].y++;
	}
	
	//Left
	else if ((direction & (1<<LEFT)) && paddles[0].y && (matrix[paddles[0].x][paddles[0].y - 1] != PADDLE_MARK)){
	    paddles[0].y--;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[0].x][paddles[0].y+i] = PADDLE_MARK;
	}
		
}


void update_RightPaddle(int direction){
	//Updating value to zero
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[1].x+i][paddles[1].y] = 0;
	}
	
	int collision_flag = 0;
	
	if ((direction & (1<<UP)) && paddles[1].x && (matrix[paddles[1].x - 1][paddles[1].y] != PADDLE_MARK)){
		//Up
		paddles[1].x--;
	}
	else if ((direction & (1<<DOWN)) && (paddles[1].x < MAT_ROW-PADDLE_LEN) && (matrix[paddles[1].x + PADDLE_LEN][paddles[1].y] != PADDLE_MARK)){
		//Down
		paddles[1].x++;
	}
	
	if ((direction & (1<<RIGHT)) && (paddles[1].y < MAT_COL-1) && (matrix[paddles[1].x][paddles[1].y + 1] != PADDLE_MARK)){
		//Right
		paddles[1].y++;
	}
	else if ((direction & (1<<LEFT)) && (paddles[1].y > MAT_COL-MAX_PADDLE_MOVEMENT)){
		//Left
		
		for(int i = 0; i<PADDLE_LEN; i++){
			if(matrix[paddles[1].x+i][paddles[1].y-1] == PADDLE_MARK){
				collision_flag = 1;
			}
		}
		if(!collision_flag){
			paddles[1].y--;
		}
		//paddles[1].y--;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[1].x+i][paddles[1].y] = PADDLE_MARK;
	}
}


void update_BottomPaddle(int direction){
	//Updating value to zero
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[2].x][paddles[2].y + i] = 0;
	}
	
	int collision_flag = 0;
	
	if ((direction & (1<<UP)) && (paddles[2].x > MAT_ROW-MAX_PADDLE_MOVEMENT)){
		//Up
		
		for(int i = 0; i<PADDLE_LEN; i++){
			if(matrix[paddles[2].x-1][paddles[2].y+i] == PADDLE_MARK){
				collision_flag = 1;
			}
		}
		if(!collision_flag){
			paddles[2].x--;
		}
		//paddles[2].x--;
	}
	else if ((direction & (1<<DOWN)) && paddles[2].x < MAT_ROW-1 && (matrix[paddles[2].x + 1][paddles[2].y] != PADDLE_MARK)){
		//Down
		paddles[2].x++;
	}
	
	
	if ((direction & (1<<RIGHT)) && (paddles[2].y < MAT_COL-PADDLE_LEN) && (matrix[paddles[2].x][paddles[2].y + PADDLE_LEN] != PADDLE_MARK)){
		//Right
		paddles[2].y++;
	}
	else if ((direction & (1<<LEFT)) && paddles[2].y && (matrix[paddles[2].x][paddles[2].y - 1] != PADDLE_MARK)){
		//Left
		paddles[2].y--;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[2].x][paddles[2].y+i] = PADDLE_MARK;
	}
}


void update_LeftPaddle(int direction){
	//Updating value to zero
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[3].x+i][paddles[3].y] = 0;
	}
	
	int collision_flag = 0;
	
	if ((direction & (1<<UP)) && paddles[3].x && (matrix[paddles[3].x - 1][paddles[3].y] != PADDLE_MARK)){
		//Up
		paddles[3].x--;
	}
	
	else if ((direction & (1<<DOWN)) && (paddles[3].x < MAT_ROW-PADDLE_LEN) && (matrix[paddles[3].x + PADDLE_LEN][paddles[3].y] != PADDLE_MARK)){
		//Down
		paddles[3].x++;
	}
	
	
	if ((direction & (1<<RIGHT)) && (paddles[3].y < MAX_PADDLE_MOVEMENT-1)){
		//Right
		for(int i = 0; i<PADDLE_LEN; i++){
			if(matrix[paddles[3].x+i][paddles[3].y + 1] == PADDLE_MARK){
				collision_flag = 1;
			}
		}
		if(!collision_flag){
			paddles[3].y++;
		}
		//paddles[3].y++;
	}
	
	else if ((direction & (1<<LEFT)) && paddles[3].y && (matrix[paddles[3].x][paddles[3].y - 1] != PADDLE_MARK)){
		//Left
		paddles[3].y--;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[3].x+i][paddles[3].y] = PADDLE_MARK;
	}
}

void movePaddle(int direction, int idx) {
	/* move paddle[idx] 1 unit along the direction */
	if(idx == 0){
		update_TopPaddle(direction);
	}
	else if(idx == 1){
		update_RightPaddle(direction);
	}
	else if(idx == 2){
		update_BottomPaddle(direction);
	}
	else {
		update_LeftPaddle(direction);
	}
}