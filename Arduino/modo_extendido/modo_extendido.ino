void set_output() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}



void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);

  set_output();
}

// Pines asignados a cada segmento
const int segmentPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };  // Assign pins to segments (a, b, c, d, e, f, g, dp)

// Pines asignados a las direcciones
const int directionPins[] = { 10, 11 };

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
void bcd2sevenseg(int num) {
  if (num >= 0 && num <= 9) {
    byte data_converted = sevenSegmentMap[num];

    for (int i = 0; i < 8; i++) {
      digitalWrite(segmentPins[i], bitRead(data_converted, i));
    }
  }
}

void setDirection(uint8_t dir) {
  for (int i = 0; i < 2; i++) {
    digitalWrite(directionPins[i], bitRead(dir, i));
  }
}

uint8_t count = 0;

void splitDigits(uint8_t number, uint8_t &units, uint8_t &tens, uint8_t &hundreds) {

  hundreds = number / 100;
  tens = (number % 100) / 10;
  units = number % 10;
}



void loop() {

  if (digitalRead(12) == 1) {
    uint8_t unidades;
    uint8_t decenas;
    uint8_t centenas;
    splitDigits(count, unidades, decenas, centenas);

    setDirection(0);
    bcd2sevenseg(unidades);
    delay(1);
    setDirection(0xf);

    setDirection(1);
    bcd2sevenseg(decenas);
    delay(1);
    setDirection(0xf);

    setDirection(2);
    bcd2sevenseg(centenas);
    delay(1);
    setDirection(0xf);

    count++;
  }
  delay(500);
}
