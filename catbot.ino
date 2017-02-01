#include <Servo.h>

const int sXPin = 10;           // first servo pin
const int sYPin = 11;           // second servo pin
const int laserPin = 12;        // pin for the laser
const int joySw = 9;                // pin for the joystick switch
const int joyH = 0;             // Joy X axis analog pin
const int joyV = 1;             // Joy Y axis analog pin
const int interval = 15;        // time between each reading

const boolean serialOut = true;

int joyVal;                     // variable to store the analog value from the joystick

boolean currentState = LOW;     // current button state
boolean lastState = LOW;        // last button state
boolean laserState = LOW;        // last button state

Servo servoX;                   // create servo object to control a servo
Servo servoY;                   // create servo object to control a servo

void setup() {

  servoX.attach(sXPin);         // attaches the servo for the X axis
  servoY.attach(sYPin);         // attaches the servo for the X axis

  pinMode(laserPin, OUTPUT);    // set the laser pin as OUTPUT
  pinMode(joySw, INPUT_PULLUP); // set the joystick switch pin as INPUT with a pullup resistor

  digitalWrite(laserPin, HIGH); // set the laser on!
  if (serialOut == true) {
    Serial.begin(9600);           // serial communication to see analog value from the stick
  }
}


void loop(){
  currentState = digitalRead(joySw);

  if (serialOut == true) {
    serialValues();
  }

  checkButtonState();

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
  Serial.print ("!joy:");
  Serial.print(analogRead(joyH));
  Serial.print (",");
  Serial.print(analogRead(joyV));
  Serial.println (";");
}

/* check if the button is pushed / relased */
void checkButtonState(){
  currentState = digitalRead(joySw);
  if (currentState == HIGH && lastState == LOW){//if button has just been pressed
    if (serialOut == true) {
      Serial.println("!btn:released");
    }
    if (laserState == HIGH) {
      if (serialOut == true) {
        Serial.println("!lzr:on=>off");
      }
      laserState = LOW;
      digitalWrite(laserPin, laserState);
    } else {
      if (serialOut == true) {
        Serial.println("!lzr:off=>on");
      }
      laserState = HIGH;
      digitalWrite(laserPin, laserState);
    }
  } else if(currentState == LOW && lastState == HIGH && serialOut == true){
    Serial.println("!btn:pressed");
  }
  lastState = currentState;
}

