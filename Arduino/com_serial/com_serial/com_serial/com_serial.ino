
#include <avr/io.h>
#include <avr/interrupt.h>

int state = LOW;
int R16, R17;// variables a utilizar en el barrido
// Tabla de conversión de binario a 7 segmentos 
unsigned char display7seg[10] = {0b10111111, 0b10000110, 0b11011011, 0b11001111, 0b11100110, 0b11101101, 0b11111101, 0b10000111, 0b11111111, 0b11101111};
unsigned char unidad, decena, centena; 

unsigned char valor3;
uint8_t data_send ;
unsigned char receivedData;

//***************************************************************
//com serial configuration

void setupUSART() {
  // Set the baud rate to 9600 for 16MHz clock (for example)
    int baud = 103;
  UBRR0H = (unsigned char)(baud>>8); //configurar velocidad
  UBRR0L = (unsigned char)baud;
  UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); //Habilitar interrupción por recepción
  UCSR0C = 0b00000110; //8 bits de datos; no paridad y 1 bit de parada

}

//***************************************************************
//timer 1 configuration
void setupTIMER1() {   
  TCCR1A = 0b00000000;// modo toggle desactivado y ctc 
  TCCR1B = 0b00001100;// modo ctc y reloj 256 
  OCR1A = 31250; 
  TIMSK1 = 0b00000010;//comparador A 
}

//***************************************************************
//gpio and general configuration
void setup() {
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
  setupUSART(); // Initialize USART configuration
  setupTIMER1();
  sei(); // Enable global interrupts
}


//***************************************************************
//function for display sweept
void put_in_display (uint8_t data){
  for (int i = 2; i <= 9; i++) {
    // Use bitwise AND to check the status of each bit
    if (bitRead(data, i - 2) == HIGH) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}

void put_in_power (uint8_t data){
  for(int i = 10; i<=12; i++){
    if (bitRead(data, i-10) == HIGH) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}

//***************************************************************
//function encoding units, tens and hundreds into common cathode 7seg display
void BIN7SEG(unsigned char valor3) {
  R16=valor3;
  //Barrido de displays 
    Bin_BCD3_centena: 
    R16 = R16-100; 
    if (R16<0) {goto Bin_BCD3_decena;}
     R17++;
    goto Bin_BCD3_centena;
    Bin_BCD3_decena:
    R16 = R16+100; 
    centena=R17; R17=0; 
    Bin_BCD3_decena1:
     R16=R16-10; 
     if (R16<0) {goto Bin_BCD3_unidad;}
     R17++; 
     goto Bin_BCD3_decena1; 
     Bin_BCD3_unidad:
     R16=R16+10; 
     decena=R17; 
     unidad=R16; 
     R17 = 0;
    put_in_display(display7seg[unidad]);
    put_in_power(0b11111110);
    delay(1);
    put_in_power(255); 
    put_in_display(display7seg[decena]); 
    put_in_power(0b11111101);
    delay(1);
    put_in_power(255); 
    put_in_display(display7seg[centena]);
    put_in_power(0b11111011);
    delay(1);
    put_in_power(255); 
}

//***************************************************************
//Interruption for data reception
ISR(USART_RX_vect) {
  receivedData = UDR0; // Read the received data
  // Process received data here
  //USART_Transmit(receivedData);
 
}

//***************************************************************
//Interruption for timer overflow
ISR(TIMER1_COMPA_vect){
   //Se transmite cuando el timer realiza la interrupción
   USART_Transmit(data_send);
}

//***************************************************************
//data transmission function
void USART_Transmit(unsigned char data) {
  // Wait for the transmit buffer to be empty
  while (!(UCSR0A & (1 << UDRE0)));
  // Put data into the transmit buffer
  UDR0 = data;
}


//***************************************************************
//MAIN LOOP
void loop() {
 
  int adcValue = analogRead(A0);              // 10 bits adc range 0 - 1023
  float data_f = float(adcValue)*255 / 1023;  // la conversion requiere de decimales, usar variables float o double 
  data_send = data_f;
  //
   BIN7SEG(receivedData); // note el barrido siempre se esta ejecutando
  delay(1);
}

