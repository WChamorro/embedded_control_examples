#include <TimerOne.h>

// Define the table (2D array)
int senoidal[255] = { 
  0x80,
0x83,
0x86,
0x89,
0x8C,
0x8F,
0x92,
0x95,
0x98,
0x9B,
0x9E,
0xA2,
0xA5,
0xA7,
0xAA,
0xAD,
0xB0,
0xB3,
0xB6,
0xB9,
0xBC,
0xBE,
0xC1,
0xC4,
0xC6,
0xC9,
0xCB,
0xCE,
0xD0,
0xD3,
0xD5,
0xD7,
0xDA,
0xDC,
0xDE,
0xE0,
0xE2,
0xE4,
0xE6,
0xE8,
0xE9,
0xEB,
0xED,
0xEE,
0xF0,
0xF1,
0xF3,
0xF4,
0xF5,
0xF6,
0xF7,
0xF8,
0xF9,
0xFA,
0xFB,
0xFC,
0xFC,
0xFD,
0xFD,
0xFE,
0xFE,
0xFE,
0xFE,
0xFE,
0xFE,
0xFE,
0xFE,
0xFE,
0xFE,
0xFD,
0xFD,
0xFC,
0xFC,
0xFB,
0xFA,
0xFA,
0xF9,
0xF8,
0xF7,
0xF6,
0xF4,
0xF3,
0xF2,
0xF0,
0xEF,
0xED,
0xEC,
0xEA,
0xE8,
0xE7,
0xE5,
0xE3,
0xE1,
0xDF,
0xDD,
0xDB,
0xD8,
0xD6,
0xD4,
0xD2,
0xCF,
0xCD,
0xCA,
0xC8,
0xC5,
0xC2,
0xC0,
0xBD,
0xBA,
0xB7,
0xB5,
0xB2,
0xAF,
0xAC,
0xA9,
0xA6,
0xA3,
0xA0,
0x9D,
0x9A,
0x97,
0x94,
0x91,
0x8E,
0x8A,
0x87,
0x84,
0x81,
0x7E,
0x7B,
0x78,
0x75,
0x71,
0x6E,
0x6B,
0x68,
0x65,
0x62,
0x5F,
0x5C,
0x59,
0x56,
0x53,
0x50,
0x4D,
0x4A,
0x48,
0x45,
0x42,
0x3F,
0x3D,
0x3A,
0x37,
0x35,
0x32,
0x30,
0x2D,
0x2B,
0x29,
0x27,
0x24,
0x22,
0x20,
0x1E,
0x1C,
0x1A,
0x18,
0x17,
0x15,
0x13,
0x12,
0x10,
0xF,
0xD,
0xC,
0xB,
0x9,
0x8,
0x7,
0x6,
0x5,
0x5,
0x4,
0x3,
0x3,
0x2,
0x2,
0x1,
0x1,
0x1,
0x1,
0x1,
0x1,
0x1,
0x1,
0x1,
0x1,
0x2,
0x2,
0x3,
0x3,
0x4,
0x5,
0x6,
0x7,
0x8,
0x9,
0xA,
0xB,
0xC,
0xE,
0xF,
0x11,
0x12,
0x14,
0x16,
0x17,
0x19,
0x1B,
0x1D,
0x1F,
0x21,
0x23,
0x25,
0x28,
0x2A,
0x2C,
0x2F,
0x31,
0x34,
0x36,
0x39,
0x3B,
0x3E,
0x41,
0x43,
0x46,
0x49,
0x4C,
0x4F,
0x52,
0x55,
0x58,
0x5A,
0x5D,
0x61,
0x64,
0x67,
0x6A,
0x6D,
0x70,
0x73,
0x76,
0x79,
0x7C,

 }; // PWM values

// Counter to keep track of the index
volatile int counter = 0;

void setup() {
  Serial.begin(9600);

  // Set up PWM pin
  pinMode(9, OUTPUT); // Assuming you are using pin 9 for PWM

  // Initialize Timer1
  Timer1.initialize(392);
  Timer1.attachInterrupt(updatePWM); // Attach the interrupt function
}

// Function to update PWM based on the table values
void updatePWM() {
  int pwmValue = senoidal[counter];
  analogWrite(9, pwmValue); // Assuming you are using pin 9 for PWM

  // Increment the counter and reset it if it reaches the end
  counter++;
  if (counter >= 255) {
    counter = 0;
  }
}

void loop() {
  // The loop is empty because the PWM output is updated in the interrupt function
}
