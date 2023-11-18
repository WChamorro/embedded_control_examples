#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveData);
  Serial.begin(38400); 
}

void loop() {
  delay(100);
}


void requestEvent() {
  Wire.write("hol"); // respond with message of 6 bytes
  }

  void receiveData(int howMany)
{
  while(1 < Wire.available()) 
  {
    char c = Wire.read(); 
    Serial.print(c);         
  }
  int x = Wire.read();    
  Serial.println(x);         
}