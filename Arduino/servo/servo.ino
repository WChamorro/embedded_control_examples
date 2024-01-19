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
  for (int angle = 300; angle <= 2100; angle += 200) {
    myServo.write(angle);     // Set the servo angle
    delay(500);                // Wait for the servo to reach the angle
  }

delay(500);

  // Move the servo motor from 180 to 0 degrees
  for (int angle = 2100; angle >= 0; angle -= 100) {
    myServo.write(angle);     // Set the servo angle
    delay(500);                // Wait for the servo to reach the angle
  }
  delay(500);
}
