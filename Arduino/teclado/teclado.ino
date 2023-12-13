#include <Keypad.h>

const byte ROWS = 4; /* four rows */
const byte COLS = 4; /* four columns */
/* define the symbols on the buttons of the keypads */
char hexaKeys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','x'},
  {'1','2','3','-'},
  {'*','0','=','+'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; /* connect to the row pinouts of the keypad */
byte colPins[COLS] = {2, 3, 4, 5}; /* connect to the column pinouts of the keypad */

/* initialize an instance of class NewKeypad */
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
Serial.begin(9600);
}

void loop(){
  char customKey = customKeypad.getKey();

  if (customKey){
Serial.println(customKey);
  }
}