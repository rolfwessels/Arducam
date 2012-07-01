#include <Servo.h>

Servo myservo; 
int pos = 90;            //servo position
int stepSize = 1;        //servo stepsize
const int servoOut = 9;

const int joyH = 5;        // L/R Parallax Thumbstick
const int joyV = 4;        // U/D Parallax Thumbstick

int inByte = 0;          // incoming serial byte


void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  myservo.attach(servoOut);
  myservo.write(pos);
}

void loop()
{
  updateFromSerial();
  updateFromJoystick();
    
  setServoToPos();
  delay(10);
}

void updateFromJoystick()
{
  int joystick_pos = analogRead(joyH);
  if (joystick_pos < 400)
  {
    decPos(1);
  }
  
  if (joystick_pos > 600)
  {
    incPos(1);
  }  
//  outputJoystick();
}

void updateFromSerial()
{
  if (Serial.available() > 0) 
  {
    inByte = Serial.read();

    if (inByte == 'j') {
      decPos(2);
    }
    
    if (inByte == 'f') {
      incPos(2);
    }
    
    if (inByte == 'm') {
      pos = 90;
    }
  }
}

void setServoToPos() {
      myservo.write(pos);
}

void incPos(int stepSize) {
  if (pos < 170) {
    pos = pos + stepSize;
    if (pos > 170) {
      pos = 170;
    }
  }
}

void decPos(int stepSize) {
  if (pos > 10) {
    pos = pos - stepSize;
    if (pos < 10 ) {
      pos = 10;
    }
  }
}

/**
* Display joystick values
*/
void outputJoystick(){

    Serial.print(analogRead(joyH));
    Serial.print ("---"); 
    Serial.print(analogRead(joyV));
    Serial.println ("----------------");
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}
