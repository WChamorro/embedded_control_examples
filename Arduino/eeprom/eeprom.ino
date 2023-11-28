
void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
/* Wait for completion of previous write */
while(EECR & (1<<EEPE));
/* Set up address and Data Registers */
EEAR = uiAddress;
EEDR = ucData;
/* Write logical one to EEMPE */
EECR |= (1<<EEMPE);
/* Start eeprom write by setting EEPE */
EECR |= (1<<EEPE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
/* Wait for completion of previous write */
while(EECR & (1<<EEPE));
/* Set up address register */
EEAR = uiAddress;
/* Start eeprom read by writing EERE */
EECR |= (1<<EERE);
/* Return data from Data Register */
return EEDR;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {
  
  int pin2 = digitalRead(2);
  int pin3 = digitalRead(3);
  int pin4 = digitalRead(4);
  int pin5 = digitalRead(5);

  byte packedByte = 0; // Initialize the byte

  packedByte |= (pin2 << 0); // Store pin2 value in the least significant bit
  packedByte |= (pin3 << 1); // Store pin3 value in the second least significant bit
  packedByte |= (pin4 << 2); // Store pin4 value in the third least significant bit
  packedByte |= (pin5 << 3);

  if(packedByte!=0){

  EEPROM_write(0x10,packedByte);
  Serial.print("eeprom write ");
  Serial.println(packedByte);

  }
 delay(1000);
  unsigned char data_read;
  data_read = EEPROM_read(0x10);
    Serial.print("eeprom read ");
  Serial.println(data_read);
 delay(1000);
}
