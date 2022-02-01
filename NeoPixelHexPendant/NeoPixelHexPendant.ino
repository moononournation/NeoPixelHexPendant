#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
  #include <avr/pgmspace.h>
#endif

#define PIN            3
#define NUMPIXELS      37
#define HUESHIFT       (1024)

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

const byte spiral[] PROGMEM = {21,27,32,36,35,34,33,28,22,15,9,4,0,1,2,3,8,14,20,26,31,30,29,23,16,10,5,6,7,13,19,25,24,17,11,12,18};
#define DELAYMS 10

void setup() {
#if defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); // This initializes the NeoPixel library.
}

static uint16_t first_hue = 0;
void loop() {
  for (uint16_t i = 0; i < sizeof(spiral); i++) {
    pixels.setPixelColor(pgm_read_byte_near(spiral + i), pixels.ColorHSV(first_hue + (i * HUESHIFT), 255, 7));
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

  first_hue -= HUESHIFT / 128; // fading steps
  // delay(DELAYMS);
}
