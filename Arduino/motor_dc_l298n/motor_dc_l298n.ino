// Define the pins connected to the L298N motor driver
const int ENA = 5;  // Enable pin for Motor A
const int IN1 = 7;  // Input 1 for Motor A
const int IN2 = 6;  // Input 2 for Motor A

void setup() {
  // Set the motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Start with the motor stopped
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  // Run the motor forward
  motorControl(50, HIGH, LOW);  // Speed = 255 (0-255), Forward

  delay(2000); // Run for 2 seconds

  // Run the motor backward
  motorControl(255, LOW, HIGH);  // Speed = 200 (0-255), Backward

  delay(2000); // Run for 2 seconds

  // Stop the motor
  motorControl(0, LOW, LOW);  // Speed = 0, Stop

  delay(2000); // Pause for 2 seconds
}

// Function to control the motor with PWM
void motorControl(int speed, int in1State, int in2State) {
  analogWrite(ENA, speed); // Set speed via PWM
  digitalWrite(IN1, in1State);
  digitalWrite(IN2, in2State);
}
