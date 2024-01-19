const int analogInputPin0 = A0;  // Analog input pin A0 connected to AIN0
const int analogInputPin1 = A1;  // Analog input pin A1 connected to AIN1
const int ledPin = 13;           // LED connected to digital pin 13

void setup() {
  pinMode(analogInputPin0, INPUT);
  pinMode(analogInputPin1, INPUT);
  pinMode(ledPin, OUTPUT);

  // Enable the analog comparator
  ACSR |= _BV(ACIE);  // Enable analog comparator interrupt
  ACSR &= ~_BV(ACD);  // Enable the analog comparator (clear ACD bit)
}

void loop() {
  // Your main code goes here
}

// Analog comparator interrupt service routine
ISR(ANALOG_COMP_vect) {
  if (ACSR & _BV(ACO)) {
    // AIN0 > AIN1
    digitalWrite(ledPin, HIGH);
  } else {
    // AIN0 <= AIN1
    digitalWrite(ledPin, LOW);
  }
}
