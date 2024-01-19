#include <TimerOne.h>

const int on = 13;  // Pin connected to the built-in LED on Arduino Uno
const int off = 12;

void setup() {
  pinMode(on, OUTPUT);
  pinMode(off, OUTPUT);

  // Initialize Timer1 with a callback function to toggle the pin
  Timer1.initialize(8333);  // Timer interval in microseconds 
  Timer1.attachInterrupt(togglePin);
  
}

void loop() {
  // Your main loop code here
}

// Callback function to toggle the pin
void togglePin() {
  static bool ledState = LOW;  // Initial state is LOW
  static bool ledState2 = HIGH;

  digitalWrite(on, ledState);
  digitalWrite(off, ledState2);
  ledState = !ledState;  // Toggle the state
  ledState2 = !ledState2;


}
