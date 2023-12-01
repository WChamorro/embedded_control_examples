#include <TimerOne.h>

const int ledPin = 13; // LED connected to digital pin 13
// id de los displays
byte d0=0;
byte d1=0;
byte d2=0;
byte d3=0;

void set_output() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}



const byte sevenSegmentMap[] = {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111   // 9
};

const byte controlMap[] = {
  B11111110,  // d0
  B11111101,  // d1
  B11111011,  // d2
  B11110111,  // d3
};


void setDataPins(byte value) {
  //bcd 2 7seg
  byte data_converted = sevenSegmentMap[value];
  // Pins 2 to 9 on Arduino Uno
   for (int i = 2; i <= 9; i++) {
      digitalWrite(i, bitRead(data_converted, i-2));
    }

}

void setControlPins(byte value) {
  // Pins 2 to 9 on Arduino Uno
   for (int i = 10; i <= 13; i++) {
      digitalWrite(i, bitRead(value, i-10));
    }

}



void swept(uint8_t id, uint8_t data){
  setControlPins(0xFF);
  setDataPins(data);
  setControlPins(controlMap[id]);
}

void splitDigits(uint8_t number, uint8_t &units, uint8_t &tens, uint8_t &hundreds) {

  hundreds = number / 100;
  tens = (number % 100) / 10;
  units = number % 10;
}

int display_id=0;
int count = 0;

void timerISR() {
  splitDigits(count,d0,d1,d2);
  switch (display_id) {
        case 0:
            swept(display_id,d0);
            break;
        case 1:
            swept(display_id,d1);
            break;
        case 2:
            swept(display_id,d2);
            break;
        default:
            swept(display_id,d3);
            break;
    }
    display_id++;
    if(display_id>3){
      display_id=0;
    }
}


void setup() {
  set_output();
  // Configure Timer1 to generate an interrupt every 8.33ms
  Timer1.initialize(8333); // Set the timer period in microseconds
  Timer1.attachInterrupt(timerISR); // Attach the ISR function to the timer interrupt
  sei();
}


void loop() {
  count+=15;
  delay(800);
}


