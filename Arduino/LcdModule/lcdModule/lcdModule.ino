#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows
int time;
int phase;

void setup() {
  lcd.init();  // initialize the lcd
  lcd.backlight();
  time = 15;
  phase = 2;
}

void loop() {
  int n = 5;

  int score[6] = { 0, 0, 0, 10, 0, 0 };
  while (n--) {

    int currentPlayer = 3;

    if (phase == 1) {
      lcd.setCursor(0, 0);            // move cursor to   (0, 0)
      lcd.print(" P1 P2 P3 P4 P5 ");  // print message at (0, 0)


      // lcd.print();
      lcd.setCursor(1, 1);
      lcd.print(score[1]);

      lcd.setCursor(4, 1);
      lcd.print(score[2]);

      lcd.setCursor(7, 1);
      lcd.print(score[3]);

      lcd.setCursor(10, 1);
      lcd.print(score[4]);

      lcd.setCursor(13, 1);
      lcd.print(score[5]);
    }
    
    
    else if (phase == 2) {
      if (time == 9) {
        lcd.clear();
      }
      lcd.setCursor(0, 0);  // move cursor to   (0, 0)
      lcd.print(" MAGUIRE   TIME ");
      lcd.setCursor(1, 1);
      lcd.print("P");
      lcd.setCursor(2, 1);
      lcd.print(currentPlayer);
      lcd.setCursor(3, 1);
      lcd.print(":");
      lcd.setCursor(4, 1);
      lcd.print(score[currentPlayer]);
      lcd.setCursor(11, 1);
      lcd.print(time);
      if (time == 0) {
        lcd.clear();
        phase = 1;
        time = 15;
      }
    }
  }
if(phase == 2){
  time--;
}
  delay(1000);
}
