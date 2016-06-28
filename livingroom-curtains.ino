#include <Wire.h>
#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, 13, 12); // 13-PUL,12-DIR
int togglePin = 8;

void setup()
{
  Serial.begin(9600);
  Serial.println("READY");
  stepper.setAcceleration(1000);
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(1500);
  pinMode(togglePin, OUTPUT);
  digitalWrite(togglePin, LOW);
}
long current_position;

void loop()
{
  if (stepper.run() != true) {
    digitalWrite(togglePin, LOW);
    if (Serial.available() > 0) {
     Serial.end();
     Serial.begin(9600);
     digitalWrite(togglePin, HIGH);
     current_position = stepper.currentPosition();
     if(current_position>=9500) {
      stepper.moveTo(0);
     }
     else if(current_position<=0) {
      stepper.moveTo(9500);
     }
    stepper.run(); 
  }
 }
}

