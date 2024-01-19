#include <TimerOne.h>

const int s1 = 13;  // Pin connected to the built-in LED on Arduino Uno
const int s2 = 12;
const int s3 = 11;
const int s4 = 10;
const float delta = 0.8;
const int on = 5000;
const int state_size = 4;
volatile int state_index = 0;

void setup() {
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(9, OUTPUT);

  // Initialize Timer1 with a callback function to toggle the pin
  Timer1.initialize(on);  // Timer interval in microseconds (1 second)
  Timer1.attachInterrupt(togglePin);
  
}

void loop() {
  // Your main loop code here
}

// Callback function to toggle the pin
void togglePin() {
  static bool ledState  = HIGH;  // Initial state is LOW
  static bool ledState2 = LOW;

  ledState = !ledState;  // Toggle the state
  ledState2 = !ledState2;

  if(ledState==HIGH){
    Timer1.initialize(on);
    Timer1.restart();
  }else{
    float t_on = float(on)*delta;
    Timer1.initialize(int(t_on));
    Timer1.restart();   
  }
  digitalWrite(9, ledState);
    state_index = (state_index + 1) % state_size;
  
  switch (state_index) {
  case 0:
    digitalWrite(s1, HIGH);
    digitalWrite(s2, HIGH);
    digitalWrite(s4, LOW);
    digitalWrite(s3, LOW);
    break;
  case 1:
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    digitalWrite(s4, LOW);
    digitalWrite(s3, HIGH);
    break;

  case 2:
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s4, HIGH);
    digitalWrite(s3, HIGH);
    break;  

  case 3:
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    digitalWrite(s4, HIGH);
    digitalWrite(s3, LOW);
    break; 
  default: 
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s4, LOW);
    digitalWrite(s3, LOW);

  }

}
