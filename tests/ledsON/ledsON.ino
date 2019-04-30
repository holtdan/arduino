#include <arduino.h>

int ledBL = 3; // BottomLeft to TopRight
int ledBR = 5;
int ledTR = 6;
int ledTL = 9;

void setup() {
  // nothing happens in setup
}

void loop() {
  analogWrite(ledBL,255);
  analogWrite(ledBR,255);
  analogWrite(ledTR,255);
  analogWrite(ledTL,255);
  delay(10000);
}
