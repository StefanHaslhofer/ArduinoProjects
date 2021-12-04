#include <Adafruit_NeoPixel.h>

#define LED_PIN   6  // any PWM capable pin
#define NUM_LEDS 60

int serialData;
char dmx_buffer[512];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_RGBW + NEO_KHZ800);

void setup()
{
  strip.begin();
  strip.setBrightness(80); // set brightness to n%
  turnOffPixels();
  Serial.begin(115200);
}

void loop()
{
  while(Serial.read() != 0x7E) {}
  while(Serial.read() != 0x06) {}
  while(Serial.read() == -1) {} //size LSB
  while(Serial.read() == -1) {} //size MSB
  while(Serial.read() == -1) {} //always 0x00
  for(int n=0; n<512; n++) {
    dmx_buffer[n] = Serial.read();
    
  }
  setLedsBasedOnSerialData(dmx_buffer[0]);
}

/*
 * processes serial data and turns on or off the leds
 */
void setLedsBasedOnSerialData(byte serialData) {
  // 2 means build succeeded
  if(serialData == 2 || serialData == 0x32) {
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
