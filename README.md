# Maguire-in-the-Middle
Maguire in the Middle is a 5-player game where one player tries to catch a ball and the other four players try to inhibit the catching. The total duration of the game is 2 minutes and 30 seconds, and played using 4 joysticks and 1 gyroscope. 

## How to Play
The game has 5 players in each round. There is a player in the middle, who is the 'Maguire'. The other four players are on four sides, each having a paddle board (like the ones in DX-Ball game). There is a ball in the board, which keeps moving around following physical laws, rebounding off walls and the 4 players’ paddles. The four players on the sides pass the ball to each other. 

Each player has a defined region of 2 rows where he can move his paddle around to control/direct the ball in a manner such that Maguire can’t intercept easily. Maguire will gain a point whenever he successfully intercepts a pass. 

Each player becomes Maguire in turn. Each round consists of 30 seconds time limit. The player with the most interception in his 30 seconds of playtime being Maguire will have scored the most points, and thus, will win. 

## Components
Gameplay is controlled by an ATMega32A and an Arduino UNO.

The game screen is a 16x16 bicolorable LED Dot Matrix, created using 4 8x8 bicolorable LED Dot Matrix and 6 decoder IC's.

The time and points are shown using a 16x2 LCD display module. 

4 Joysticks are used to control 4 paddles around the screen, and a gyroscope (MPU 6050) is used to direct the movement of the Maguire. 

## Circuit Diagram
![](https://github.com/ishrak26/Maguire-in-the-Middle/blob/main/Circuit/ProjectFinalCkt.BMP)

## Demo Video
