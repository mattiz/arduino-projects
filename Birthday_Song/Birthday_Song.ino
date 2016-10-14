#define __AVR_ATtiny84__
#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
volatile boolean f_wdt = 1;




const int Note_C  = 239;
const int Note_CS = 225;
const int Note_D  = 213;
const int Note_DS = 201;
const int Note_E  = 190;
const int Note_F  = 179;
const int Note_FS = 169;
const int Note_G  = 159;
const int Note_GS = 150;
const int Note_A  = 142;
const int Note_AS = 134;
const int Note_B  = 127;



//#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 4

//SoftwareSerial mySerial(rxPin, txPin);



int blinkPin = 0;
int speakerPin = 1;
int sensorPin = 7;

void setup()
{
  pinMode(blinkPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  digitalWrite(blinkPin, LOW);
  
  //mySerial.begin(9600);

  setup_watchdog(8);
}


void TinyTone(unsigned char divisor, unsigned char octave, unsigned long duration) {
  TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  //TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
  delay(duration);
  TCCR1 = 0x90;              // stop the counter
}


void tune() {
  int d = 10;

  TinyTone(Note_C, 4, 500);
  delay(d);
  TinyTone(Note_D, 4, 500);
  delay(d);
  TinyTone(Note_E, 4, 500);
  delay(d);
  TinyTone(Note_F, 4, 500);
  delay(d);
  TinyTone(Note_G, 4, 1000);
  delay(d);
  TinyTone(Note_G, 4, 1000);
  delay(d);
  TinyTone(Note_A, 4, 500);
  delay(d);
  TinyTone(Note_A, 4, 500);
  delay(d);
  TinyTone(Note_A, 4, 500);
  delay(d);
  TinyTone(Note_A, 4, 500);
  delay(d);
  TinyTone(Note_G, 4, 1500);
  delay(d);
  TinyTone(Note_F, 4, 500);
  delay(d);
  TinyTone(Note_F, 4, 500);
  delay(d);
  TinyTone(Note_F, 4, 500);
  delay(d);
  TinyTone(Note_F, 4, 500);
  delay(d);
  TinyTone(Note_E, 4, 1000);
  delay(d);
  TinyTone(Note_E, 4, 1000);
  delay(d);
  TinyTone(Note_D, 4, 500);
  delay(d);
  TinyTone(Note_D, 4, 500);
  delay(d);
  TinyTone(Note_D, 4, 500);
  delay(d);
  TinyTone(Note_D, 4, 500);
  delay(d);
  TinyTone(Note_C, 4, 1500);
}


void loop()
{
  digitalWrite(blinkPin, HIGH); // turn on power to photo resistor before sampling
  delay(1);
  int v = analogRead(sensorPin);
  digitalWrite(blinkPin, LOW);

  if( v < 400 ) {
    // light
    //digitalWrite(blinkPin, LOW);
    tune();
    
  } else {
    // dark
    //digitalWrite(blinkPin, HIGH);
  }


  system_sleep();
  

  //mySerial.println(v);
}


// set system into the sleep state 
// system wakes up when wtchdog is timed out
void system_sleep() {
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                        // System sleeps here

  sleep_disable();                     // System continues execution here when watchdog timed out 
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {

  byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);

}
  
// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  f_wdt=1;  // set global flag
}
