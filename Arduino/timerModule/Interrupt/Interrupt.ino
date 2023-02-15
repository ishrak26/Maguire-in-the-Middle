#include <TimerOne.h>
#include <avr/sleep.h>

// This example uses the timer interrupt to blink an LED
// and also demonstrates how to share a variable between
// the interrupt and the main program.


const int led = 13;  // the pin with a LED

void setup(void)
{
  pinMode(led, OUTPUT);
  Timer1.initialize(500000);
  Timer1.attachInterrupt(counter); // blinkLED to run every 0.15 seconds
  Serial.begin(9600);
}


// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledState = LOW;
volatile unsigned long count = 0; // use volatile for shared variables

void counter(void)
{
  count = count + 1;
  if (count == 10) {
    ledState = HIGH;
  } 
  digitalWrite(led, ledState);
}


// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void)
{
  unsigned long countCopy;  // holds a copy of the blinkCount

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
  noInterrupts();
  countCopy = count;
  interrupts();

  Serial.print("Counter: ");
  Serial.println(10 - countCopy);
  if (countCopy == 10) {
    delay(100); 
    exit(0);
  }
  delay(500); 
}
