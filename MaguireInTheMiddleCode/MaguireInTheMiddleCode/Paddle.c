/* assigned to Anonto */


#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

#define MAT_ROW 16
#define MAT_COL 16
#define PADDLE_LEN 5
#define MAG_SIZE 2
#define MAX_PADDLE_MOVEMENT 3


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
unsigned char matrix[MAT_ROW][MAT_COL];



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
	paddles[0].x = 0
	paddles[0].y = 6
	
	//right
	paddles[1].x = 6
	paddles[1].y = 15
	
	//bottom
	paddles[0].x = 15
	paddles[0].y = 6
	
	//left
	paddles[0].x = 6
	paddles[0].y = 0
	
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
	else if(((direction & (1<<RIGHT)) != 0) && (paddles[0].y != MAT_COL-1)){
	    paddles[0].y = paddles[0].y + 1;
	}
	
	//Down
	else if(((direction & (1<<DOWN)) != 0) && (paddles[0].x < MAX_PADDLE_MOVEMENT-1)){
	    paddles[0].x = paddles[0].x + 1;
	}
	
	//Left
	else if(((direction & (1<<LEFT)) != 0) && (paddles[0].y != 0)){
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
		matrix[paddles[0].x+i][paddles[0].y] = 0;
	}
	
	//Up
	if(((direction & (1<<UP)) != 0) && (paddles[0].x != 0)){
		paddles[0].x = paddles[0].x - 1;
	}
	
	//Right
	else if(((direction & (1<<RIGHT)) != 0) && (paddles[0].y != 0)){
		paddles[0].y = paddles[0].y + 1;
	}
	
	//Down
	else if(((direction & (1<<DOWN)) != 0) && (paddles[0].x != MAT_ROW-1)){
		paddles[0].x = paddles[0].x + 1;
	}
	
	//Left
	else if(((direction & (1<<LEFT)) != 0) && (paddles[0].y > MAT_COL-MAX_PADDLE_MOVEMENT)){
		paddles[0].y = paddles[0].y - 1;
	}
	
	//Updating current paddle co-ordinates
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[0].x+i][paddles[0].y] = 1;
	}
}


void update_BottomPaddle(int direction){
	//Updating value to zero
	for(int i = 0; i<PADDLE_LEN; i++){
		matrix[paddles[2].x][paddles[2].y+i] = 0;
	}
	
	//Up
	if(((direction & (1<<UP)) != 0) && (paddles[2].x > MAT_ROW-MAX_PADDLE_MOVEMENT)){
		paddles[2].x = paddles[2].x - 1;
	}
	
	//Right
	else if(((direction & (1<<RIGHT)) != 0) && (paddles[2].y != MAT_COL-1)){
		paddles[2].y = paddles[2].y + 1;
	}
	
	//Down
	else if(((direction & (1<<DOWN)) != 0) && (paddles[2].x != 0)){
		paddles[2].x = paddles[2].x + 1;
	}
	
	//Left
	else if(((direction & (1<<LEFT)) != 0) && (paddles[2].y != 0)){
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
	else if(((direction & (1<<RIGHT)) != 0) && (paddles[3].y < MAX_PADDLE_MOVEMENT-1)){
		paddles[3].y = paddles[3].y + 1;
	}
	
	//Down
	else if(((direction & (1<<DOWN)) != 0) && (paddles[3].x != MAT_COL-1)){
		paddles[3].x = paddles[3].x + 1;
	}
	
	//Left
	else if(((direction & (1<<LEFT)) != 0) && (paddles[3].y != 0)){
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
		update_TopPaddle(int direction);
	}
	else if(idx == 1){
		update_RightPaddle(int direction);
	}
	else if(idx == 2){
		update_BottomPaddle(int direction);
	}
	else if(idx == 3){
		update_LeftPaddle(int direction);
	}
}