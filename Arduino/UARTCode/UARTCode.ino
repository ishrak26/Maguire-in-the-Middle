#include<SoftwareSerial.h>

SoftwareSerial SUART(2, 3); //RX = DPin-2; TX = DPin-3

int flag = 1;

void setup() {
  Serial.begin(9600);
  SUART.begin(9600);
}

void loop() {
  byte n = SUART.available();
  if (n != 0)
  {
    int x = SUART.read();
    Serial.print(x);
    if (flag) Serial.print(',');
    else Serial.print(' ');
    flag ^= 1;
  }
}
