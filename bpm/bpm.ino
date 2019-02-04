// Create variables for the pins we'll be using:
int lightSensor = A2;
int buttonPin = A4;
int switchPin = A9;

int redRGBLED = 12;
int greenRGBLED = 13;
int blueRGBLED = 14;
class Bob
{
  public:
  unsigned long Tic;
};
//Bob bill = nil;
void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(blueRGBLED,OUTPUT);

  // Initialize the serial monitor
  Serial.begin(9600);
  // bill = new Bob();
}
unsigned long NextBeat = 0;
unsigned long NextOff = 0;
unsigned long LastBeat = 0;
unsigned long BeatInterval = 500; // 120 BPM
bool BeatOn = false;

bool buttonPinOn = false;
unsigned long TempoTap1 = 0;
unsigned long TempoTap2 = 0;
float BPM(unsigned long interval)
{
  return (1.0/interval) * 60.0 * 1000;
}
void loop()
{
  unsigned long tic = millis();
  if (tic >= NextBeat)
  {
    NextBeat = tic + BeatInterval;
    NextOff = tic + 10;//(BeatInterval/8);

    Serial.print("Beat: ");
    Serial.println(tic);
    Serial.print("NextBeat: ");
    Serial.println(NextBeat);
    Serial.print("NextOff : ");
    Serial.println(NextOff);
    
    digitalWrite(blueRGBLED,HIGH);
    BeatOn = true;
  }
  else if (BeatOn && tic >= NextOff)
  {
    digitalWrite(blueRGBLED,LOW);
    BeatOn = false;
    Serial.print("Off: ");
    Serial.println(tic);
  }
  /////////////////////////////////////////////
  // Tempo Tapping?
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && !buttonPinOn)
  {
    Serial.println("Press! ");
    buttonPinOn = true;
    if (TempoTap1 == 0)
      TempoTap1 = millis();
    else
    {
        TempoTap2 = millis();

        Serial.print("Tempo2: ");
        Serial.println(TempoTap2);
        Serial.print("Tempo1: ");
        Serial.println(TempoTap1);
        
        BeatInterval = BPM(TempoTap2-TempoTap1);
        NextBeat = 0;
        NextOff = 0;
        BeatOn = false;
        TempoTap1 = TempoTap2;

        Serial.print("New Beat Interval: ");
        Serial.println(BeatInterval);
    }
  }
  else if (buttonState != LOW)
    buttonPinOn = false;
}
