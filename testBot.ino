#include <Servo.h>

const int sXPin = 10;           // first servo pin
const int sYPin = 11;           // second servo pin
const int laserPin = 12;        // pin for the laser
const int joyH = 0;             // Joy X axis
const int joyV = 1;             // Joy Y axis
const int interval = 15;        // time between each reading

int joyVal;                     // variable to store the analog value from the joystick

Servo servoX;                   // create servo object to control a servo
Servo servoY;                   // create servo object to control a servo

void setup() {

  servoX.attach(sXPin);         // attaches the servo for the X axis
  servoY.attach(sYPin);         // attaches the servo for the X axis

  pinMode(laserPin, OUTPUT);    // sers

  Serial.begin(9600);           // serial communication to see analog value from the stick
}


void loop(){
  digitalWrite(laserPin, HIGH);
  // Display Joystick values using the serial monitor
  serialValues();

  // Read the horizontal joystick value  (value between 0 and 1023)
  joyVal = analogRead(joyH);
  joyVal = map(joyVal, 1023, 0, 0, 180);     // scale it to use it with the servo (result  between 0 and 180)

  servoX.write(joyVal);                         // sets the servo position according to the scaled value

  // Read the horizontal joystick value  (value between 0 and 1023)
  joyVal = analogRead(joyV);
  joyVal = map(joyVal, 1023, 0, 0, 180);     // scale it to use it with the servo (result between 70 and 180)

  servoY.write(joyVal);                           // sets the servo position according to the scaled value

  delay(interval);                                       // waits for the servo to get there

}

/**
* Display joystick values
*/
void serialValues(){

  Serial.print(analogRead(joyH));
  Serial.print (",");
  Serial.print(analogRead(joyV));
  Serial.println (";");
}
