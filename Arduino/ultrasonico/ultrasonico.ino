const int trigPin = 9; // Trigger pin of the HC-SR04
const int echoPin = 10; // Echo pin of the HC-SR04

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;
  double d;
  
  // Clear the trigger pin and wait for sensor to settle
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send a pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH); // duration in us
  
  // Calculate the distance
  distance = (duration * 0.0343) / 2; // Speed of sound in air is approximately 0.0343 cm/µs
  d = double(duration)*0.000343/2;
  // Print the distance on the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print(d);
  Serial.println(" m");
  delay(500); // Wait before taking the next measurement
}
