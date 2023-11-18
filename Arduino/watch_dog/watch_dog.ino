#include <avr/io.h>
// ISR interrupt service routine
#include <avr/interrupt.h>
#define wdt_reset() __asm__ __volatile__ ("wdr")
const int pLED = 13; // LED at Pin13
int idx;
int accum_delay = 0;

// Install the interrupt routine for Watchdog Interrupt
ISR(WDT_vect)
{
Serial.println("WDT on");
flash();
}

void config_wdt(){
cli();
MCUSR &= ~(1<<WDRF);
WDTCSR |= (1<<WDCE) | (1<<WDE); // Start timed sequence
WDTCSR = (1<<WDIE) | (1<<WDP2) | (1<<WDP1); // Set new prescaler = 128K cycles(~1 s)
// si se agrega  (1<<WDE) se resetea el sistema 
sei();
}

void setup()
{
Serial.begin(9600);
pinMode(pLED, OUTPUT);
digitalWrite(pLED, LOW);
config_wdt();
Serial.print("WDTCSR: ");
Serial.println(WDTCSR, HEX);
Serial.println("Setup finished.");
}
void loop()
{
config_wdt();
idx++;
Serial.print("delay of: "); // do anything
Serial.println(idx*100); 
delay(idx*100); // change argument to 1500 -> watchdog will be active

}
void flash()
{
static boolean output = HIGH;
digitalWrite(pLED, output);
output = !output;
idx = 0;
}