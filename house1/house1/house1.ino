#include <arduino.h>

int ledStepDelayMS = 30; // 10 for debugging, 30 for real
int flickerOffMS = 30;

int ledBL = 3; // BottomLeft to TopRight
int ledBR = 5;
int ledTR = 6;
int ledTL = 9;

class RoomPass
{
  public:
    int LedPin;
    int Value;
    RoomPass(int ledPin)
    {
      LedPin = ledPin;
      Value = 0;
    }
};
RoomPass rps[] =
{
  RoomPass(ledBL),
  RoomPass(ledBR),
  RoomPass(ledTR),
  RoomPass(ledTL)
};

void setup() {
  // nothing happens in setup
}

void loop() {
  cycle1(ledBL);
  cycle1(ledBR);
  cycle1(ledTR);
  cycle1(ledTL);
  randWaitSecs(4,9);
  cycle1(ledTR);
  cycle1(ledBR);
  cycle1(ledBL);
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
  int peakHold = random(2,6);
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
  randWaitSecs(3,6);
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
