// NeoPixel simple sketch (c) 2013 Shae Erisson, adapted to tinyNeoPixel library by Spence Konde 2019.
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#if (F_CPU>7370000) //neopixel library required 7.37MHz minimum clock speed; this line is used to skip this sketch in internal testing. It is not needed in your sketches.

#include <tinyNeoPixel_Static.h>
#include <avr/power.h>

#define PIN                 3
#define NUMPIXELS           37
#define HUE_FACTOR          3
#define BRIGHTNESS_DIVIDER  16
#define DELAY_MS            27

// Since this is for the static version of the library, we need to supply the pixel array
// This saves space by eliminating use of malloc() and free(), and makes the RAM used for
// the frame buffer show up when the sketch is compiled.

byte pixels[NUMPIXELS * 3];


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.

tinyNeoPixel leds = tinyNeoPixel(NUMPIXELS, PIN, NEO_GRB, pixels);

const byte spiral[] PROGMEM = {21,27,32,36,35,34,33,28,22,15,9,4,0,1,2,3,8,14,20,26,31,30,29,23,16,10,5,6,7,13,19,25,24,17,11,12,18};

void setup() {
#if defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  clock_prescale_set(clock_div_1);
#endif

  pinMode(PIN,OUTPUT);
  //with tinyNeoPixel_Static, you need to set pinMode yourself. This means you can eliminate pinMode()
  //and replace with direct port writes to save a couple hundred bytes in sketch size (note that this
  //savings is only present when you eliminate *all* references to pinMode).
  //leds.begin() not needed on tinyNeoPixel
}

static byte first_hue = 192;
void loop() {
  for (uint16_t i = 0; i < sizeof(spiral); i++) {
    leds.setPixelColor(pgm_read_byte_near(spiral + i), Wheel(first_hue + (i * HUE_FACTOR))); // Moderately bright green color.
  }
  leds.show(); // This sends the updated pixel color to the hardware.

  first_hue--;
  delay(DELAY_MS);
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  // WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return leds.Color((255 - WheelPos * 3) / BRIGHTNESS_DIVIDER, 0, (WheelPos * 3) / BRIGHTNESS_DIVIDER);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return leds.Color(0, (WheelPos * 3) / BRIGHTNESS_DIVIDER, (255 - WheelPos * 3) / BRIGHTNESS_DIVIDER);
  }
  WheelPos -= 170;
  return leds.Color((WheelPos * 3) / BRIGHTNESS_DIVIDER, (255 - WheelPos * 3) / BRIGHTNESS_DIVIDER, 0);
}
#else //neopixel library required 7.37MHz minimum clock speed; these and following lines are used to skip this sketch in internal testing. It is not needed in your sketches.
#warning "Neopixel control requires F_CPU > 7.37MHz"
void setup() {}
void loop() {}
#endif
