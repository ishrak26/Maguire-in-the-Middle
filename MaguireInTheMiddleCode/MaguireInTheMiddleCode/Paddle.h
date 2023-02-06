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
			matrix[paddles[j].x][paddles[j].y+i] = 1;
		}
	}
	for (int j = 1; j < 4; j += 2) {
		for(int i = 0; i<PADDLE_LEN; i++){
			matrix[paddles[j].x+i][paddles[j].y] = 1;
		}
	}
	
}

void update_TopPaddle(int direction){
	
	//Updating value to zero 
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[0].x][paddles[0].y+i] = 0;
	}
	
	//Up
	if ((direction & (1<<UP)) && paddles[0].x && (matrix[paddles[0].x - 1][paddles[0].y] != 1)){
		paddles[0].x--;
	}
	//Down
	else if ((direction & (1<<DOWN)) && (paddles[0].x < MAX_PADDLE_MOVEMENT-1) && (matrix[paddles[0].x + 1][paddles[0].y] != 1)){
		paddles[0].x++;
	}
	
	//Right
	if ((direction & (1<<RIGHT)) && (paddles[0].y < MAT_COL-PADDLE_LEN) && (matrix[paddles[0].x][paddles[0].y + 1] != 1)){
	    paddles[0].y++;
	}
	
	//Left
	else if ((direction & (1<<LEFT)) && paddles[0].y && (matrix[paddles[0].x][paddles[0].y - 1] != 1)){
	    paddles[0].y--;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[0].x][paddles[0].y+i] = 1;
	}
		
}


void update_RightPaddle(int direction){
	//Updating value to zero
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[1].x+i][paddles[1].y] = 0;
	}
	
	if ((direction & (1<<UP)) && paddles[1].x && (matrix[paddles[1].x - 1][paddles[1].y] != 1)){
		//Up
		paddles[1].x--;
	}
	else if ((direction & (1<<DOWN)) && (paddles[1].x < MAT_ROW-PADDLE_LEN) && (matrix[paddles[1].x + 1][paddles[1].y] != 1)){
		//Down
		paddles[1].x++;
	}
	
	if ((direction & (1<<RIGHT)) && (paddles[1].y < MAT_COL-1) && (matrix[paddles[1].x][paddles[1].y + 1] != 1)){
		//Right
		paddles[1].y++;
	}
	else if ((direction & (1<<LEFT)) && (paddles[1].y > MAT_COL-MAX_PADDLE_MOVEMENT) && (matrix[paddles[1].x][paddles[1].y - 1] != 1)){
		//Left
		paddles[1].y--;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[1].x+i][paddles[1].y] = 1;
	}
}


void update_BottomPaddle(int direction){
	//Updating value to zero
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[2].x][paddles[2].y + i] = 0;
	}
	
	
	if ((direction & (1<<UP)) && (paddles[2].x > MAT_ROW-MAX_PADDLE_MOVEMENT) && (matrix[paddles[2].x - 1][paddles[2].y] != 1)){
		//Up
		paddles[2].x--;
	}
	else if ((direction & (1<<DOWN)) && paddles[2].x < MAT_ROW-1 && (matrix[paddles[2].x + 1][paddles[2].y] != 1)){
		//Down
		paddles[2].x++;
	}
	
	
	if ((direction & (1<<RIGHT)) && (paddles[2].y < MAT_COL-PADDLE_LEN) && (matrix[paddles[2].x][paddles[2].y + 1] != 1)){
		//Right
		paddles[2].y++;
	}
	else if ((direction & (1<<LEFT)) && paddles[2].y && (matrix[paddles[2].x][paddles[2].y - 1] != 1)){
		//Left
		paddles[2].y--;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[2].x][paddles[2].y+i] = 1;
	}
}


void update_LeftPaddle(int direction){
	//Updating value to zero
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[3].x+i][paddles[3].y] = 0;
	}
	
	if ((direction & (1<<UP)) && paddles[3].x && (matrix[paddles[3].x - 1][paddles[3].y] != 1)){
		//Up
		paddles[3].x--;
	}
	
	else if ((direction & (1<<DOWN)) && (paddles[3].x < MAT_ROW-PADDLE_LEN) && (matrix[paddles[3].x + 1][paddles[3].y] != 1)){
		//Down
		paddles[3].x++;
	}
	
	
	if ((direction & (1<<RIGHT)) && (paddles[3].y < MAX_PADDLE_MOVEMENT-1) && (matrix[paddles[3].x][paddles[3].y + 1] != 1)){
		//Right
		paddles[3].y++;
	}
	
	else if ((direction & (1<<LEFT)) && paddles[3].y && (matrix[paddles[3].x][paddles[3].y - 1] != 1)){
		//Left
		paddles[3].y--;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[3].x+i][paddles[3].y] = 1;
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