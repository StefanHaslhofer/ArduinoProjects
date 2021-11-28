#include <Adafruit_NeoPixel.h>

#define LED_PIN   6  // any PWM capable pin
#define NUM_LEDS 150

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_RGBW + NEO_KHZ800);

void setup()
{
  strip.begin();
  strip.setBrightness(80); // set brightness to n%
}

void loop()
{
  turnOnPixels(strip.Color(0, 150, 0));
}

/*
 * sets strip color to 000 (off)
 */
void turnOffPixels()
{
  for (byte i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

/*
 * sets strip color based on parameter
 */
void turnOnPixels(uint32_t color)
{
  turnOffPixels();
  
  for (byte i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, color);
  }
  strip.show();
}
