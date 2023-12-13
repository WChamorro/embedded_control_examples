#include <Servo.h>

// Create a servo object
Servo myServo;

// Define the pin connected to the servo
const int servoPin = 7;

void setup() {
  // Attach the servo to the pin
  myServo.attach(servoPin);
}

void loop() {
  // Move the servo motor from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle += 10) {
    myServo.write(angle);     // Set the servo angle
    delay(500);                // Wait for the servo to reach the angle
  }

  // Move the servo motor from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle -= 10) {
    myServo.write(angle);     // Set the servo angle
    delay(15);                // Wait for the servo to reach the angle
  }
}
