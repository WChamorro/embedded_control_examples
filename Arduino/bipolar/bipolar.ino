// Define pins for the motor coils
const int coil_A_pin1 = 8;
const int coil_A_pin2 = 9;
const int coil_B_pin1 = 10;
const int coil_B_pin2 = 11;

// Define the full step sequence for bipolar motor
const int full_step_sequence[][4] = {
  {1, 0, 1, 0},
  {1, 0, 0, 1},
  {0, 1, 0, 1},
  {0, 1, 1, 0}
};

void setup() {
  // Set motor coil pins as outputs
  pinMode(coil_A_pin1, OUTPUT);
  pinMode(coil_A_pin2, OUTPUT);
  pinMode(coil_B_pin1, OUTPUT);
  pinMode(coil_B_pin2, OUTPUT);
}

void step(int direction, int steps, int delay_time) {
  int step_number = 0;
  int steps_left = abs(steps);
  int step_count = sizeof(full_step_sequence) / sizeof(full_step_sequence[0]);

  // Loop to perform steps
  while (steps_left > 0) {
    // Move forward or backward based on direction
    if (direction == 1) {
      step_number = (step_number + 1) % step_count;
    } else {
      step_number = (step_number - 1 + step_count) % step_count;
    }

    // Set coil pins according to the sequence
    for (int i = 0; i < 4; i++) {
      digitalWrite(coil_A_pin1 + i, full_step_sequence[step_number][i]);
    }

    delay(delay_time); // Delay between steps
    steps_left--;
  }
}

void loop() {
  // Rotate the motor 100 steps forward with a delay of 5ms between steps
  step(1, 10, 400);
  delay(1000); // Pause for 1 second
  
  // Rotate the motor 100 steps backward with a delay of 5ms between steps
  step(0, 10, 400);
  delay(1000); // Pause for 1 second
}
