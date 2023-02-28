                                                  // Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <math.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
#include <avr/sleep.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows

SoftwareSerial SUART(2, 3);

Adafruit_MPU6050 mpu;

int playerScores[5];
volatile int gameState = 0;
int winner[5]; // all the winners (there can be tie)
volatile int winnerCnt = 0;
volatile int beforeGame = 1;

int tone_pin = 8;

unsigned int reload = 0xF424; // every 1 second
volatile int count;

char welcome_text[20] = "Welcome To";
char game_name_upper[20] = "Maguire In";
char game_name_lower[20] = "The Middle";

ISR(TIMER1_COMPA_vect)
{
  count--;
  if (count == -1) {
    TIMSK1 &= ~(1 << OCIE1A);
  }
}

void findWinner() {
  if (winnerCnt == 0) {
    winnerCnt = 1;
    winner[0] = (gameState>>1);                        
  }
  else if (playerScores[(gameState>>1)] > winner[winnerCnt-1]) {
    winnerCnt = 1;
    winner[0] = (gameState>>1);  
  }  
  else if (playerScores[(gameState>>1)] == winner[winnerCnt-1]) {
    // tie
    winner[winnerCnt++] = (gameState>>1);       
  }
  lcd.clear();
  gameState++;
}

void setup(void) {
  cli();
  initialize_timer();
  TIMSK1 &= ~(1<<OCIE1A);
  sei();
  
  Serial.begin(9600);
  SUART.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  initialize_gyro();
  
  lcd.init();  // initialize the lcd
  lcd.backlight();

  delay(100);
}

void initialize_gyro() {
  //Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    //Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  //Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  //Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    //Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    //Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    //Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    //Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  //Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    //Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    //Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    //Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    //Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  //Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    //Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    //Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    //Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    //Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    //Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    //Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    //Serial.println("5 Hz");
    break;
  }
}

void initialize_timer() {
  // initialize timer1
  count = 30;
  
  TCCR1A = 0;
  TCCR1B = 0; 
  OCR1A = reload;
  TCCR1B = (1<<WGM12) | (1<<CS12); 
  TIMSK1 = (1<<OCIE1A); 
   
}

void loop() {
  //lcd.clear();
  
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  float dx, dy, x, y;
  x = a.acceleration.x;
  y = a.acceleration.y;
  dx = (fabs(x))*12.7;
  dy = (fabs(y))*12.7;
  if(x < 0){
    dx = -dx; 
  }
  if(y < 0){
    dy = -dy; 
  }
  int maguire_dx , maguire_dy;
  maguire_dx = dx/31.0;
  maguire_dy = dy/31.0;
  maguire_dx += 5;
  maguire_dy += 5;
  unsigned char dxs = maguire_dx;
  unsigned char dys = maguire_dy;

  byte n = SUART.available();
  char ch;
  if(n != 0){
      ch = SUART.read();

      if(ch == 'g'){    
        SUART.write(dxs);
        delay(10);
        SUART.write(dys);
        delay(10);
      }
  }
  
  if (gameState&1) {
    if (!(TIMSK1 & (1<<OCIE1A))) {
      findWinner();
      return;    
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Maguire:");

    lcd.setCursor(9, 0);
    lcd.print((gameState>>1));    
    
    lcd.setCursor(0, 1);
    lcd.print("Score:");

    lcd.setCursor(7, 1);
    lcd.print(playerScores[(gameState>>1)]);
        
    if (n != 0 && ch == 's') {
      playerScores[(gameState>>1)]++;
      tone(tone_pin, 1300, 300); 
    }  
    lcd.setCursor(11, 0);
      lcd.print("Time:");
      int countCopy = count;
      if (countCopy == 9) {
        lcd.setCursor(12, 1);
        lcd.print(" ");    
      } 
      lcd.setCursor(11, 1);    
      lcd.print(countCopy);     
  } 
  else {
    if (gameState == 10) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Game has ended!");
      delay(1000);
      // lcd.setCursor(1, 0);
      if (winnerCnt > 1) {
        lcd.setCursor(1, 0);
        lcd.print("Tie betn players"); 
        lcd.setCursor(5, 1);
        lcd.print(winner[0]);           
        for (int i = 1; i < winnerCnt; i++) {
          lcd.setCursor(2*i-1, 1);
          lcd.print(",");
          lcd.setCursor(2*i, 1);
          lcd.print(winner[i]); 
        }      
      }
      else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Winner: Player"); 
        lcd.setCursor(15, 0);
        lcd.print(winner[0]); 
        lcd.setCursor(0, 1);
        lcd.print("Score:");
        lcd.setCursor(7, 1);
        lcd.print(playerScores[winner[0]]);          
      }  
      delay(10000);     
    } 
    else if (gameState == 0 && beforeGame) {
        unsigned int i=0;
        lcd.setCursor(3, 0);
        
        while(welcome_text[i]!='\0'){
          lcd.print(welcome_text[i]);
          delay(200);
          i++;          
        } 
        delay(500);
        // clear screen
        lcd.clear();  

        i=0;
        lcd.setCursor(3, 0);
        
        while(game_name_upper[i]!='\0'){
          lcd.print(game_name_upper[i]);
          delay(200);         
          i++;          
        }  

        i=0;
        lcd.setCursor(3, 1);
        
        while(game_name_lower[i]!='\0'){
          lcd.print(game_name_lower[i]);
          delay(200);         
          i++;          
        } 
        delay(1000);
        // clear screen
        lcd.clear(); 
        delay(100);
        beforeGame = 0;          
    }    
    else {
      lcd.setCursor(0, 0);
      lcd.print("Press button to"); 
      lcd.setCursor(0, 1);
      lcd.print("begin playing!"); 

      
      if(n != 0 && ch == 'a'){              
        gameState++;
        lcd.clear();
        initialize_timer();
      }      
    }          
  }

  //delay(200);
}