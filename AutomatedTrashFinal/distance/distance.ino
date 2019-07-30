#include <Servo.h>
Servo sg90;

const int buzzer    = 8;
const int servo_pin = 5;
const int trig_pin  = 3;
const int echo_pin  = 4;
//const int whiteLED  = 7;

int doorIsOpen = 0;

float duration;
int   distance;

void setup()
{
//    digitalWrite(whiteLED,  HIGH);

  Serial.begin(9600);

  sg90.attach(servo_pin);
  sg90.write(145);
  
  pinMode(whiteLED,  OUTPUT);
//  digitalWrite(whiteLED,  HIGH);
  
  pinMode (trig_pin, OUTPUT);
  pinMode (echo_pin, INPUT);

  Serial.println("Automated Trash");
  delay(2000);
}

void loop()
{
  int Distance = getDistance();

  Serial.print(Distance);
  Serial.println(" cm");
  delay(200);

  if ( Distance > 0 && Distance <= 10 )
  {
    tone(buzzer, 700, 100);
    delay(70);
    noTone(buzzer);
    tone(buzzer, 900, 250);
    //Serial.println("Door is Open");
    sg90.write(55);
    delay(1000);  
    noTone(buzzer);
    delay(2000);
    doorIsOpen = 1;
  }
  else if ( doorIsOpen == 1 && Distance >= 10)
  {
    //Serial.println("Door is close");
    doorIsOpen = 0;
    close_the_door();
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


void close_the_door()
{
  for ( int i = 55; i <= 145; i++) //  door open = 55 degree, doorclose = 145 degree;
  {
    sg90.write(i);
    delay(25);
  }
}
