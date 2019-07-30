const int trig_pin  = 2;
const int echo_pin  = 3;
const int buzzer    = 4;
const int greenLED  = 8;
const int orangeLED = 9;
const int redLED    =10;
const int whiteLED  =11;

float duration;
int   distance;

void setup()
{
  Serial.begin(9600);
  Serial.println("Automated Trash - Height Control");

  pinMode (trig_pin, OUTPUT);
  pinMode (echo_pin, INPUT);
  
  pinMode(whiteLED,  OUTPUT);
  pinMode(greenLED,  OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(redLED,    OUTPUT);
 
  delay(2000);
}

void loop()
{
  digitalWrite(whiteLED,  HIGH);

  int height = getDistance();

  Serial.print(height);
  Serial.println(" cm");
  delay(200);
  LEDcontrol(height);
  
}

void LEDcontrol(int height)
{
  if (height > 0 && height < 6 )  // 75% & above
  {
    digitalWrite(whiteLED,  HIGH);
    digitalWrite(greenLED,  HIGH);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(redLED,    HIGH);
    buzzerTone();

  }
  
  else if (height < 10)          // 50% - 75%
  {
    digitalWrite(whiteLED,  HIGH);
    digitalWrite(greenLED,  HIGH);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(redLED,    LOW);
    
  }
  else if (height < 14)         // 25% - 50%
  {
    digitalWrite(whiteLED,  HIGH);
    digitalWrite(greenLED,  HIGH);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED,    LOW);
  }
  else                          // 00% - 25%
  {
    digitalWrite(whiteLED,  HIGH);
    digitalWrite(greenLED,  LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED,    LOW);

  }
}

float getDistance()
{
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn (echo_pin, HIGH);
  distance = (duration / 2) / 29;
  return distance;
}

void buzzerTone()
{
  tone( buzzer, 1000, 200);
  delay(200);
  noTone(buzzer);
  delay(200);
  
  tone( buzzer, 1000, 200);
  delay(200);
  noTone(buzzer);
  delay(200);
  
  tone( buzzer, 1000, 400);
  delay(250);
  noTone(buzzer);
  delay(1000);
}
