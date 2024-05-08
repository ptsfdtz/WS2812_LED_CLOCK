#include <FastLED.h>
#include "header.h"
#include <deque>
#define LED_PIN 5
#define NUM_LEDS 65
#define BRIGHTNESS 20
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define PUSH_KEY 12
#define UP_KEY 13
#define DOWN_KEY 14

unsigned long buttonPressedTime = 0;
boolean isButtonPressed = false;
int button = 0;
std::deque<int> ledQueue;
CRGB leds[NUM_LEDS];
int xDimension = 13, yDimension = 5;

int calculateIndex(int x, int y) {
  if (x > 13 || y > 5) return -1;
  return y == 1 ? 65 - x : y == 2 ? 38 + x : y == 3 ? 39 - x : y == 4 ? 12 + x : y == 5 ? 13 - x : -1;
}

void setup() {
  pinMode(PUSH_KEY, INPUT_PULLUP); pinMode(UP_KEY, INPUT_PULLUP); pinMode(DOWN_KEY, INPUT_PULLUP);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  SHOW_HELLO();
}

void loop() {
  if (digitalRead(UP_KEY) == LOW && button > 0) { button--; delay(200); }
  if (digitalRead(DOWN_KEY) == LOW && button < 4) { button++; delay(200); }
  switch (button) {
    case 0: SHOW_HELLO(); break;
    case 1: showLoveAndSea(); break;
    case 2: showRainBow(); break;
    case 3: second(); break;
    case 4: radiateFromCenter(); break;
  }
  FastLED.show();
}

void SHOW_HELLO() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  setColorForCoordinates(H_COLOR, H_LOCATION, num_H);
  setColorForCoordinates(E_COLOR, E_LOCATION, num_E);
  setColorForCoordinates(L_COLOR, L_LOCATION, num_L);
  setColorForCoordinates(l_COLOR, l_LOCATION, num_l);
  setColorForCoordinates(O_COLOR, O_LOCATION, num_O);
}

void setColorForCoordinates(const CRGB& color, const int (*coordinates)[2], int numCoordinates) {
  for (int i = 0; i < numCoordinates; i++) {
    int index = calculateIndex(coordinates[i][0], coordinates[i][1]);
    if (index != -1) leds[index] = color;
  }
}

void showLoveAndSea() {
  static uint8_t hue = 0;
  for (int x = 0; x < xDimension; x++) for (int y = 0; y < yDimension; y++) leds[calculateIndex(x + 1, y + 1)] = (calculateIndex(x + 1, y + 1) != -1) ? CHSV((hue - 8 * x) % 256, 255, 255) : leds[calculateIndex(x + 1, y + 1)];
  setColorForCoordinates(colorLove, Love, numLove);
  FastLED.show();
  hue--;
  delay(100);
}

void showRainBow() {
  static uint8_t hue = 0;
  for (int x = 0; x < xDimension; x++) for (int y = 0; y < yDimension; y++) if (int index = calculateIndex(x + 1, y + 1); index != -1) leds[index] = CHSV((8 * x + hue) % 256, 255, 255);
  FastLED.show();
  hue++;
  delay(100);
}

void second() {
  uint32_t currentTime = millis();
  for (int x = 1; x <= xDimension; x++) for (int y = 1; y <= yDimension; y++) if (int index = calculateIndex(x, y), distance = abs(x - 1) + abs(y - 1), brightness = 127.5 * (sin((currentTime * 0.002) + (distance * 0.1)) + 1), hue = (currentTime / 20 + distance * 10) % 256; index != -1) leds[index] = CHSV(hue, 255, brightness);
  FastLED.show();
  delay(50);
}

void radiateFromCenter() {
  uint32_t currentTime = millis();
  for (int x = 1; x <= xDimension; x++) for (int y = 1; y <= yDimension; y++) if (int index = calculateIndex(x, y), distanceToCenter = abs(x - 7) + abs(y - 3); index != -1) leds[index] = CHSV((currentTime / 10 + distanceToCenter * 10) % 256, 255, 255);
  FastLED.show();
}