#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    65
#define BRIGHTNESS  20
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int calculateIndex(int x, int y) {
  int index = 0;
  int cols = 13;

  if (y % 2 == 1) { // Odd rows
    int maxIndexRow = cols * (y / 2 + 1); // For odd rows, find the base max index for that row
    index = maxIndexRow - x; // Subtract the x value to find the correct index
  } else { // Even rows
    int minIndexRow = cols * (y / 2) - (cols - 1); // For even rows, find the base min index for that row
    index = minIndexRow + (x - 1); // Add the (x-1) value to find the correct index
  }
  
  return index;
}

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  leds[calculateIndex(2, 1)] = CRGB::Red;
  leds[calculateIndex(2, 2)] = CRGB::Red;
  leds[calculateIndex(2, 3)] = CRGB::Red;
  leds[calculateIndex(2, 4)] = CRGB::Red;
  leds[calculateIndex(2, 5)] = CRGB::Red;
  FastLED.show();
}

void loop() {}