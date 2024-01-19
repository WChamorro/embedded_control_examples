// Define pins for the motor coils
const int coil_A_1_pin = 8;
const int coil_A_2_pin = 9;
const int coil_B_1_pin = 10;
const int coil_B_2_pin = 11;

// Define the full step sequence
const int full_step[][4] = {
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

const int wave_drive[][4] = {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};

const int half_sequence[][8] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

void setup() {
  // Set motor coil pins as outputs
  pinMode(coil_A_1_pin, OUTPUT);
  pinMode(coil_A_2_pin, OUTPUT);
  pinMode(coil_B_1_pin, OUTPUT);
  pinMode(coil_B_2_pin, OUTPUT);
  Serial.begin(9600);
}

void half_step( int sequence[][8], int direction, int steps, int delay_time) {
int step_number = 0;
  int steps_left = abs(steps);

  // Loop to perform steps
  while (steps_left > 0) {
    // Move forward or backward based on direction
    if (direction == 1) {
      step_number = (step_number + 1) % 8;
    } else {
      step_number = (step_number - 1 + 8) % 8;
    }

    // Set coil pins according to the selected sequence
    for (int i = 0; i < 8; i++) {
      digitalWrite(coil_A_1_pin + i, sequence[step_number][i]);
    }

    delay(delay_time); // Delay between steps
    steps_left--;
  }
}


void step( int sequence[][4], int direction, int steps, int delay_time) {
  int step_number = 0;
  int steps_left = abs(steps);

  // Loop to perform steps
  while (steps_left > 0) {
    // Move forward or backward based on direction
    if (direction == 1) {
      step_number = (step_number + 1) % 4;
    } else {
      step_number = (step_number - 1 + 4) % 4;
    }

    // Set coil pins according to the selected sequence
    for (int i = 0; i < 4; i++) {
      digitalWrite(coil_A_1_pin + i, sequence[step_number][i]);
    }

    delay(delay_time); // Delay between steps
    steps_left--;
  }
}

void loop() {
  // Rotate the motor 100 steps forward with a delay of 5ms between steps
  Serial.println("full step 10 horario");
  step(full_step, 1, 10, 400);
  delay(1000); // Pause for 1 second
  
  // Rotate the motor 100 steps backward with a delay of 5ms between steps
  Serial.println("full step 10 antihorario");
  step(full_step,0, 10, 400  );
  delay(1000); // Pause for 1 second
  
  Serial.println("wave drive 15 horario");
  step(wave_drive, 1, 15, 400);
  delay(1000); // Pause for 1 second
  
  // Rotate the motor 100 steps backward with a delay of 5ms between steps
  Serial.println("wave drive 15 antihorario");
  step(wave_drive,0, 15, 400  );
  delay(1000); // Pause for 1 second

  Serial.println("half step 10 horario");
  half_step(half_sequence, 1, 10, 400);
  delay(1000); // Pause for 1 second
  
  // Rotate the motor 100 steps backward with a delay of 5ms between steps
  Serial.println("half step 10 antihorario");
  half_step(half_sequence,0, 10, 400  );
  delay(1000); // Pause for 1 second
}
