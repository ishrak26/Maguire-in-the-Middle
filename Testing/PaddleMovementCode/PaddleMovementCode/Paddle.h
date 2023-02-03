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
	
}

void update_TopPaddle(int direction){
	
	//Updating value to zero 
	for(int i = 0; i<PADDLE_LEN; i++){
			matrix[paddles[0].x][paddles[0].y+i] = 0;
	}
	
	//Up
	if(((direction & (1<<UP)) != 0) && (paddles[0].x != 0)){
	    paddles[0].x = paddles[0].x - 1;
	}
	
	//Right
	if(((direction & (1<<RIGHT)) != 0) && (paddles[0].y != MAT_COL-1)){
	    paddles[0].y = paddles[0].y + 1;
	}
	
	//Down
	if(((direction & (1<<DOWN)) != 0) && (paddles[0].x < MAX_PADDLE_MOVEMENT-1)){
	    paddles[0].x = paddles[0].x + 1;
	}
	
	//Left
	if(((direction & (1<<LEFT)) != 0) && (paddles[0].y != 0)){
	    paddles[0].y = paddles[0].y - 1;
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
	
	//Up
	if(((direction & (1<<UP)) != 0) && (paddles[1].x != 0)){
		paddles[1].x = paddles[1].x - 1;
	}
	
	//Right
	if(((direction & (1<<RIGHT)) != 0) && (paddles[1].y != 0)){
		paddles[1].y = paddles[1].y + 1;
	}
	
	//Down
	if(((direction & (1<<DOWN)) != 0) && (paddles[1].x != MAT_ROW-1)){
		paddles[1].x = paddles[1].x + 1;
	}
	
	//Left
	if(((direction & (1<<LEFT)) != 0) && (paddles[1].y > MAT_COL-MAX_PADDLE_MOVEMENT)){
		paddles[1].y = paddles[1].y - 1;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[1].x+i][paddles[1].y] = 1;
	}
}


void update_BottomPaddle(int direction){
	//Updating value to zero
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[2].x][paddles[2].y+i] = 0;
	}
	
	//Up
	if ((direction & (1<<UP)) && (paddles[2].x > MAT_ROW-MAX_PADDLE_MOVEMENT)){
		paddles[2].x = paddles[2].x - 1;
	}
	
	//Right
    if(((direction & (1<<RIGHT)) != 0) && (paddles[2].y != MAT_COL-1)){
		paddles[2].y = paddles[2].y + 1;
	}
	
	//Down
	if(((direction & (1<<DOWN)) != 0) && (paddles[2].x != 0)){
		paddles[2].x = paddles[2].x + 1;
	}
	
	//Left
	if(((direction & (1<<LEFT)) != 0) && (paddles[2].y != 0)){
		paddles[2].y = paddles[2].y - 1;
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
	
	//Up
	if(((direction & (1<<UP)) != 0) && (paddles[3].x != 0)){
		paddles[3].x = paddles[3].x - 1;
	}
	
	//Right
	if(((direction & (1<<RIGHT)) != 0) && (paddles[3].y < MAX_PADDLE_MOVEMENT-1)){
		paddles[3].y = paddles[3].y + 1;
	}
	
	//Down
	if(((direction & (1<<DOWN)) != 0) && (paddles[3].x != MAT_COL-1)){
		paddles[3].x = paddles[3].x + 1;
	}
	
	//Left
	if(((direction & (1<<LEFT)) != 0) && (paddles[3].y != 0)){
		paddles[3].y = paddles[3].y - 1;
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
	else if(idx == 3){
		update_LeftPaddle(direction);
	}
}