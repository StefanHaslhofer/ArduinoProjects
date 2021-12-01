#include <Adafruit_NeoPixel.h>

#define LED_PIN   6  // any PWM capable pin
#define NUM_LEDS 150

int serialData;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_RGBW + NEO_KHZ800);

void setup()
{
  strip.begin();
  strip.setBrightness(60); // set brightness to n%
  turnOffPixels();
  Serial.begin(9600);
}

void loop()
{
  while (!Serial.available());
  serialData = Serial.readString().toInt();
  Serial.write(serialData);
  setLedsBasedOnSerialData(serialData);
}

/*
 * processes serial data and turns on or off the leds
 */
void setLedsBasedOnSerialData(byte serialData) {
  // 2 means build succeeded
  if(serialData == 2) {
    turnOnPixels(strip.Color(150, 0, 0));
  }

  delay(5000);
  turnOffPixels();
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
