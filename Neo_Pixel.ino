#include <Adafruit_NeoPixel.h>
 
#define P1 7
#define P2 8
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(16, P1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(16, P2, NEO_GRB + NEO_KHZ800);

void setup(){ 
  strip1.begin();
  strip1.setBrightness(30); //adjust brightness here
  strip1.show(); // Initialize all pixels to 'off'
  strip2.begin();
  strip2.setBrightness(30); //adjust brightness here
  strip2.show(); // Initialize all pixels to 'off'
}
 
void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(); // Red
  colorWipe(); // Green
  colorWipe(); // Blue
  rainbow();
  rainbowCycle();
}
 
// Fill the dots one after the other with a color
void colorWipe() {
  uint8_t wait = 50;
  uint32_t c1=strip1.Color(255, 0, 0);
  uint32_t c2=strip2.Color(255, 0, 0);
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, c1);
      strip1.show();
      strip2.setPixelColor(i, c2);
      strip2.show();
      delay(wait);
  }
  uint32_t c3=strip1.Color(0, 255, 0);
  uint32_t c4=strip2.Color(0, 255, 0);
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, c3);
      strip1.show();
      strip2.setPixelColor(i, c4);
      strip2.show();
      delay(wait);
  }
  uint32_t c5=strip1.Color(0, 0, 255);
  uint32_t c6=strip2.Color(0, 0, 255);
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, c5);
      strip1.show();
      strip2.setPixelColor(i, c6);
      strip2.show();
      delay(wait);
  }
}
 
void rainbow() {
  uint8_t wait=16;
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel1((i+j) & 255));
      strip2.setPixelColor(i, Wheel2((i+j) & 255));
    }
    strip1.show();
    strip2.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle() {
  uint8_t wait = 16;
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel1(((i * 256 / strip1.numPixels()) + j) & 255));
      strip2.setPixelColor(i, Wheel2(((i * 256 / strip2.numPixels()) + j) & 255));
    }
    strip1.show();
    strip2.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel1(byte WheelPos) {
  if(WheelPos < 85) {
   return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
uint32_t Wheel2(byte WheelPos) {
  if(WheelPos < 85) {
   return strip2.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip2.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip2.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
