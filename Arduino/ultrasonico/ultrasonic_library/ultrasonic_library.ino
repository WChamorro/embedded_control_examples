#include <Ultrasonic.h>

#define TRIG_PIN 9 // Pin connected to the trigger pin of HC-SR04
#define ECHO_PIN 10 // Pin connected to the echo pin of HC-SR04

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN); // Initialize Ultrasonic object

void setup() {
  Serial.begin(9600); // Start serial communication
}

void loop() {
  float distance = ultrasonic.read(); // Read distance in cm
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500); // Delay for stability
}