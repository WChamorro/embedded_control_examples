#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(38400);  // start serial for output
}

byte x = 0;

void loop() {
  Wire.beginTransmission(8); // transmit to device #4
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

  x++;

  Wire.requestFrom(8, 4);    // request 6 bytes from peripheral device #8
  while (Wire.available()) { // peripheral may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    delay(11);
  }
  Serial.println();
  delay(100);
}