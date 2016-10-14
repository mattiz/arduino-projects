#include <Adafruit_NeoPixel.h>

#define PIN         0
#define NUMPIXELS   7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.setBrightness(40);
}

void loop() {
  for(int i=0;i<NUMPIXELS;i++){

    pixels.setPixelColor(i, pixels.Color(222,115,0));

    pixels.show();

    delay(500);

  }
}
