                                                  // Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <math.h>

SoftwareSerial SUART(2, 3);

Adafruit_MPU6050 mpu;

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

  
  ////Serial.println("");
  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  //Serial.print("Acceleration X: ");
  //Serial.print(a.acceleration.x);
  //Serial.write((int) a.acceleration.x);
  //Serial.print(", Y: ");
  //Serial.print(a.acceleration.y);
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
    //Serial.print(" m/s^2             ");
  //Serial.print("dx: " );
  //Serial.print(dx);
  //Serial.print("     dy: " );
  //Serial.print(dy);  
  //Serial.println("");

  byte n = SUART.available();
  char ch;
  if(n != 0){
    ch = SUART.read();
      
    if(ch == 'g'){    
      //Serial.write(maguire_dx);
      
      //Serial.write(maguire_dy);
      //delay(200);
      Serial.print(int(dxs));
      SUART.write(dxs);
      delay(10);
      Serial.print(",");
      Serial.print(int(dys));
      SUART.write(dys);
      delay(10);
      Serial.print(" ");      
      //Serial.print(',');
      //Serial.print(maguire_dy);
      //Serial.print(" ");    
    }
    //else if (ch == 'f') {
      //Serial.print("f ");
    //}
  }
}