#include <arduino.h>

const byte digIntPin = 13;
const byte interruptPin = 2;
volatile byte mode = 0;
// 0 = long/norm
// 1 = short
// 2 = on

int ledStepDelayMS = 30; // 10 for debugging, 30 for real
int flickerOffMS = 30;

int ledBL = 3; // BottomLeft to TopRight
int ledBR = 5;
int ledTR = 6;
int ledTL = 9;

void setup() {
  // look for button press
}

void loop() {
  if (mode == 0)
    mode0();
  else if (mode == 1)
    mode1();
  else if (mode == 2)
    mode2();
}
// 2 = All On
void mode2() {
  analogWrite(ledBL,255);
  analogWrite(ledBR,255);
  analogWrite(ledTR,255);
  analogWrite(ledTL,255);
  delay(10000);
}
// 1 = Fast
void mode1() {
  cycle1(ledBL);
  cycle1(ledBR);
  cycle1(ledTR);
  cycle1(ledTL);
  cycle1(ledTR);
  cycle1(ledBR);
  cycle1(ledBL);
  delay(3000);
}
// 0 = Long/Normal mode
void mode0() {
  cycle1(ledBL);
  cycle1(ledBR);
  randWaitSecs(2,4); // get up stairs
  cycle1(ledTR);
  cycle1(ledTL);
  //randWaitSecs(4,9);
  cycle1(ledTR);
  cycle1(ledBR);
  cycle1(ledBL);
  // here it needs to wait/sleep for 2 to ?60 minutes
  randWaitSecs(2*60,15*60); // get up stairs
}
void cycle1 (int ledPin){
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    maybeFlicker(ledPin);
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(ledStepDelayMS);
  }
  int peakHold = ledPin == ledTL ? random(4,9) : random(2,6); // hold the destination room 
  for (int pk = 0; pk <= peakHold * 1000; pk += 100)
    maybeFlicker(ledPin);

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    maybeFlicker(ledPin);
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(ledStepDelayMS);
  }
  randWaitSecs(2,4);
}
void randWaitSecs(int minInc, int maxExc)
{
  delay(random(minInc, maxExc)* 1000);
}
void maybeFlicker(int ledPin)
{
  unsigned long tic = millis();
  if (0 == (tic % 7))
  {
    analogWrite(ledPin, 0);
    delay(flickerOffMS);
  }
}
