//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,2);

/* we always wait a bit between updates of the display */
unsigned long delaytime=1000;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);

  lc.shutdown(1,false);
  lc.setIntensity(1,1);
  lc.clearDisplay(1);
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void writeArduinoOnMatrix() {
  /* here is the data for the characters */
  byte a[5]={B01111110,B10001000,B10001000,B10001000,B01111110};
  byte r[5]={B00111110,B00010000,B00100000,B00100000,B00010000};
  byte d[5]={B00011100,B00100010,B00100010,B00010010,B11111110};
  byte u[5]={B00111100,B00000010,B00000010,B00000100,B00111110};
  byte i[5]={B00000000,B00100010,B10111110,B00000010,B00000000};
  byte n[5]={B00111110,B00010000,B00100000,B00100000,B00011110};
  byte o[5]={B00011100,B00100010,B00100010,B00100010,B00011100};

  byte aa[7] = {B01110000, B10001000, B10001000, B10001000, B11111000, B10001000, B10001000};
  byte rr[7] = {B11110000, B10001000, B10001000, B11110000, B10100000, B10010000, B10001000};
  byte dd[7] = {B11100000, B10010000, B10001000, B10001000, B10001000, B10010000, B11100000};
  byte uu[7] = {B10001000, B10001000, B10001000, B10001000, B10001000, B10001000, B01110000};
  byte ii[7] = {B11100000, B01000000, B01000000, B01000000, B01000000, B01000000, B11100000};
  byte nn[7] = {B10001000, B10001000, B11001000, B10101000, B10011000, B10001000, B10001000};
  byte oo[7] = {B01110000, B10001000, B10001000, B10001000, B10001000, B10001000, B01110000};

  /* now display them one by one with a small delay */
  lc.setRow(0,0,aa[0]);
  lc.setRow(0,1,aa[1]);
  lc.setRow(0,2,aa[2]);
  lc.setRow(0,3,aa[3]);
  lc.setRow(0,4,aa[4]);
  lc.setRow(0,5,aa[5]);
  lc.setRow(0,6,aa[6]);
  delay(delaytime);
  lc.setRow(1,0,rr[0]);
  lc.setRow(1,1,rr[1]);
  lc.setRow(1,2,rr[2]);
  lc.setRow(1,3,rr[3]);
  lc.setRow(1,4,rr[4]);
  lc.setRow(1,5,rr[5]);
  lc.setRow(1,6,rr[6]);
  delay(delaytime);
  lc.setRow(0,0,dd[0]);
  lc.setRow(0,1,dd[1]);
  lc.setRow(0,2,dd[2]);
  lc.setRow(0,3,dd[3]);
  lc.setRow(0,4,dd[4]);
  lc.setRow(0,5,dd[5]);
  lc.setRow(0,6,dd[6]);
  delay(delaytime);
  lc.setRow(1,0,uu[0]);
  lc.setRow(1,1,uu[1]);
  lc.setRow(1,2,uu[2]);
  lc.setRow(1,3,uu[3]);
  lc.setRow(1,4,uu[4]);
  lc.setRow(1,5,uu[5]);
  lc.setRow(1,6,uu[6]);
  delay(delaytime);
  lc.setRow(0,0,ii[0]);
  lc.setRow(0,1,ii[1]);
  lc.setRow(0,2,ii[2]);
  lc.setRow(0,3,ii[3]);
  lc.setRow(0,4,ii[4]);
  lc.setRow(0,5,ii[5]);
  lc.setRow(0,6,ii[6]);
  delay(delaytime);
  lc.setRow(1,0,nn[0]);
  lc.setRow(1,1,nn[1]);
  lc.setRow(1,2,nn[2]);
  lc.setRow(1,3,nn[3]);
  lc.setRow(1,4,nn[4]);
  lc.setRow(1,5,nn[5]);
  lc.setRow(1,6,nn[6]);
  delay(delaytime);
  lc.setRow(0,0,oo[0]);
  lc.setRow(0,1,oo[1]);
  lc.setRow(0,2,oo[2]);
  lc.setRow(0,3,oo[3]);
  lc.setRow(0,4,oo[4]);
  lc.setRow(0,5,oo[5]);
  lc.setRow(0,6,oo[6]);
  delay(delaytime);
  lc.setRow(1,0,0);
  lc.setRow(1,1,0);
  lc.setRow(1,2,0);
  lc.setRow(1,3,0);
  lc.setRow(1,4,0);
  lc.setRow(1,5,0);
  lc.setRow(1,6,0);
  delay(delaytime);
}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
  for(int row=0;row<8;row++) {
    delay(delaytime);
    lc.setRow(0,row,B10100000);
    delay(delaytime);
    lc.setRow(0,row,(byte)0);
    for(int i=0;i<row;i++) {
      delay(delaytime);
      lc.setRow(0,row,B10100000);
      delay(delaytime);
      lc.setRow(0,row,(byte)0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns() {
  for(int col=0;col<8;col++) {
    delay(delaytime);
    lc.setColumn(0,col,B10100000);
    delay(delaytime);
    lc.setColumn(0,col,(byte)0);
    for(int i=0;i<col;i++) {
      delay(delaytime);
      lc.setColumn(0,col,B10100000);
      delay(delaytime);
      lc.setColumn(0,col,(byte)0);
    }
  }
}

/* 
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,true);
        delay(delaytime);
      }
    }
  }
}

void loop() { 
  writeArduinoOnMatrix();
  //rows();
  //columns();
  //single();
}
