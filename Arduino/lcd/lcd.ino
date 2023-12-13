#include <LiquidCrystal.h>

// LCD module connections (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Set up the number of columns and rows of the LCD
  lcd.begin(16, 2);
  
  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Hola mundo!");
  lcd.setCursor(0, 1);
  lcd.print("LCD 16x2 Test");
  delay(3000);
}

float count=2.5;
void loop() {
lcd.setCursor(0, 1);
lcd.print("cuenta: ") ;
lcd.print(count) ;
lcd.print("       ");
delay(500);
count+=1.7;

}
