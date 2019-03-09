//
// Create variables for the pins we'll be using:
//int lightSensor = A2;
//int buttonPin = A4;
int switchPin = A9;

//int redRGBLED = 12;
//int greenRGBLED = 13;
int blueRGBLED = 14;
class BPM
{
  public:
    BPM(int tapButtonPin)
    {
      TapButtonPin = tapButtonPin;
      pinMode(TapButtonPin, INPUT_PULLUP);

      NextBeat = 0;
      NextOff = 0;
      LastBeat = 0;
      BeatInterval = 500; // 120 BPM
      BeatOn = false;
      Debug = false;

      ButtonPinOn = false;
      TempoTap1 = 0;
      TempoTap2 = 0;
      LastTap = 0;
    }
    void Loop(unsigned long tic)
    {
      if (tic >= NextBeat)
      {
        NextBeat = tic + BeatInterval;
        NextOff = tic + 10;//(BeatInterval/8);
        BeatOn = true;
        if (Debug)
        {
          Serial.print("Beat: ");
          Serial.print(tic);
          Serial.print("  bpm 1/4: ");
          Serial.println(BeatInterval);
    
          Serial.print("NextOff : ");
          Serial.println(NextOff);
          Serial.print("NextBeat: ");
          Serial.println(NextBeat);
        }
      }
      else if (BeatOn && tic >= NextOff)
      {
        BeatOn = false;
        if (Debug)
        {
          Serial.print("Off: ");
          Serial.println(tic);
        }
      }
      /////////////////////////////////////////////
      // Tempo Tapping?
      int buttonState = digitalRead(TapButtonPin);
      if (buttonState == LOW && !ButtonPinOn)
      {
        if (Debug)
          Serial.println("Press! ");
        ButtonPinOn = true;
        if (tic - LastTap > 2000) // reset to avoid wild tempo swings between attempts
          TempoTap1 = 0;
        LastTap = tic;

        if (TempoTap1 == 0)
          TempoTap1 = millis();
        else
        {
          TempoTap2 = millis();

          if (Debug)
          {
            Serial.print("Tempo2: ");
            Serial.println(TempoTap2);
            Serial.print("Tempo1: ");
            Serial.println(TempoTap1);
          }
          BeatInterval = TempoTap2 - TempoTap1; // BPM(TempoTap2-TempoTap1);
          NextBeat = 0;
          NextOff = 0;
          BeatOn = false;
          TempoTap1 = TempoTap2;

          if (Debug)
          {
            Serial.print("New Beat Interval: ");
            Serial.println(BeatInterval);
          }
        }
      }
      else if (buttonState != LOW)
        ButtonPinOn = false;
    }
    int TapButtonPin;
    unsigned long BeatInterval;
    bool BeatOn;
    bool Debug;

  private:
    unsigned long NextBeat;
    unsigned long NextOff;
    unsigned long LastBeat;

    bool ButtonPinOn;
    unsigned long TempoTap1;
    unsigned long TempoTap2;
    unsigned long LastTap;
};
BPM bpm(A4);
void setup()
{
  //pinMode(buttonPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(blueRGBLED, OUTPUT);

  // Initialize the serial monitor
  Serial.begin(9600);
  bpm.Debug = true;
}
void loop()
{
  unsigned long tic = millis();
  int switchState = digitalRead(switchPin);
  bpm.Debug = switchState == LOW;
  bpm.Loop(tic);
  if (bpm.BeatOn)
  {
    digitalWrite(blueRGBLED, HIGH);
  }
  else
  {
    digitalWrite(blueRGBLED, LOW);
  }

  // Not sure but I guess this saves on battery...
  //delay(100);
}
