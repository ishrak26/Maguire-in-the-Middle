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

int tone_pin = 8;

volatile int count = 30; // use volatile for shared variables

void counter(void)
{
  Serial.println(gameState);
  if (gameState&1) {
    count = count - 1;
    Serial.println(count);
    if (count == -1) {
      Serial.print(" here ");
      Timer1.stop();
      Serial.print(" there ");
      if (winnerCnt == 0) {
        winnerCnt = 1;
        winner[0] = playerScores[(gameState>>1)];                        
      }
      else if (playerScores[(gameState>>1)] > winner[winnerCnt-1]) {
        winnerCnt = 1;
        winner[0] = playerScores[(gameState>>1)];  
      }  
      else if (playerScores[(gameState>>1)] == winner[winnerCnt-1]) {
        // tie
        winner[winnerCnt++] = (gameState>>1);       
      }
      lcd.clear();
      gameState++;
      Serial.print(" ttthere ");
    }
  }  
}

void setup(void) {
  Serial.begin(9600);
  SUART.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

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
  lcd.init();  // initialize the lcd
  lcd.backlight();

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(counter); 
  
  delay(100);
}

void loop() {
  if (gameState&1) {
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
    
    lcd.setCursor(1, 0);
    lcd.print("Current Maguire: Player ");

    lcd.setCursor(8, 0);
    lcd.print((gameState>>1));    
    
    lcd.setCursor(2, 1);
    lcd.print("Score");

    lcd.setCursor(2, 1);
    lcd.print(playerScores[(gameState>>1)]);

    byte n = SUART.available();
    char ch;
    if(n != 0){
      ch = SUART.read();
        
      if(ch == 'g'){    
        SUART.write(dxs);
        delay(10);
        SUART.write(dys);
        delay(10);
      } else if (ch == 's') {
        playerScores[(gameState>>1)]++;
        tone(tone_pin, 1300, 300); // temporarily turn off sound
      }   
    }
    unsigned int countCopy;  // holds a copy of the blinkCount

    // to read a variable which the interrupt code writes, we
    // must temporarily disable interrupts, to be sure it will
    // not change while we are reading.  To minimize the time
    // with interrupts off, just quickly make a copy, and then
    // use the copy while allowing the interrupt to keep working.
    noInterrupts();
    countCopy = count;
    interrupts();
    
    if (gameState&1) {
      lcd.setCursor(12, 0);
      lcd.print("Time:");

      if (countCopy == 9) {
        lcd.setCursor(13, 1);
        lcd.print(" ");    
      } 
      lcd.setCursor(12, 1);    
      lcd.print(countCopy);
    }
  } 
  else {
    if (gameState == 10) {
        lcd.setCursor(1, 0);
        lcd.print("Game has ended!");
        lcd.setCursor(1, 1);
        if (winnerCnt > 1) {
          lcd.setCursor(1, 1);
          lcd.print("Tie between players "); 
          lcd.setCursor(8, 1);
          lcd.print(winner[0]);           
          for (int i = 1; i < winnerCnt; i++) {
            lcd.setCursor(8+2*i-1, 1);
            lcd.print(",");
            lcd.setCursor(8+2*i, 1);
            lcd.print(winner[i]); 
          }      
        }
        else {
          lcd.setCursor(1, 1);
          lcd.print("Winner: Player "); 
          lcd.setCursor(8, 1);
          lcd.print(winner[0]);           
        }       
    } 
    else {
      lcd.setCursor(0, 0);
      lcd.print("Press button!");  
      
      byte n = SUART.available();
      //Serial.print(n);
      //Serial.print(" ");
      char ch;
      if(n != 0){
        ch = SUART.read();
          
        if(ch == 'a'){              
          gameState++;
          lcd.clear();
          count = 30;
        }
      }      
    }          
  }

  //delay(200);
}