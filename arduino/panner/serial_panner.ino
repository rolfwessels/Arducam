/*
  Serial Call and Response
 Language: Wiring/Arduino
 
 This program sends an ASCII A (byte of value 65) on startup
 and repeats that until it gets some data in.
 Then it waits for a byte in the serial port, and 
 sends three sensor values whenever it gets a byte in.
 
 Thanks to Greg Shakar and Scott Fitzgerald for the improvements
 
   The circuit:
 * potentiometers attached to analog inputs 0 and 1 
 * pushbutton attached to digital I/O 2
 
 Created 26 Sept. 2005
 by Tom Igoe
 modified 24 April 2012
 by Tom Igoe and Scott Fitzgerald

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialCallResponse

 */
#include <Servo.h>

Servo myservo; 
int pos = 90;            //servo position
int stepSize = 2;        //servo stepsize
const int servoOut = 9;

int inByte = 0;          // incoming serial byte

const int joyH = 4;      // L/R Parallax Thumbstick
const int joyV = 5;      // U/D Parallax Thumbstick

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  //establishContact();  // send a byte to establish contact until receiver responds 
  myservo.attach(servoOut);
  myservo.write(pos);
}

void loop()
{
  if (Serial.available() > 0) {
   
    inByte = Serial.read();

    if (inByte == 'j') {
      decPos();
//      myservo.write(pos);
      setServoToPos();
    }
    
    if (inByte == 'f') {
      incPos();
      setServoToPos();
    }
    
    if (inByte == 'm') {
      pos = 90;
//      myservo.write(pos);
      setServoToPos();
    }

    //Serial.write("pos: [%d] \n",pos);
    //Serial.writeln(pos);
    delay(10);   
  }
}

void setServoToPos() {
      myservo.write(pos);
}

void incPos() {
  if (pos < 170) {
    pos = pos + stepSize;
    if (pos > 170) {
      pos = 170;
    }
  }
}

void decPos() {
  if (pos > 10) {
    pos = pos - stepSize;
    if (pos < 10 ) {
      pos = 10;
    }
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}
