#include <FastLED.h>

#define LED_PIN 5
#define NUM_LEDS 65
#define BRIGHTNESS 20
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

const CRGB colorLove = CRGB::Red;  // 定义灯光颜色
const int Love[][2] = {
  { 4, 4 },
  { 5, 3 },
  { 5, 4 },
  { 5, 5 },
  { 6, 2 },
  { 6, 3 },
  { 6, 4 },
  { 6, 5 },
  { 7, 1 },
  { 7, 2 },
  { 7, 3 },
  { 7, 4 },
  { 8, 2 },
  { 8, 3 },
  { 8, 4 },
  { 8, 5 },
  { 9, 3 },
  { 9, 4 },
  { 9, 5 },
  { 10, 4 }
};
const int numLove = sizeof(Love) / sizeof(Love[0]);  // 计算坐标点数量

int xDimension = 13;  // 假设LED阵列的宽度
int yDimension = 5;   // 假设LED阵列的高度

int calculateIndex(int x, int y) {
  if (x > 13 || y > 5) return -1;  // 若x或y超出范围则返回-1
  // 计算LED在一维数组中的索引
  switch (y) {
    case 1: return 65 - x;
    case 2: return 38 + x;
    case 3: return 39 - x;
    case 4: return 12 + x;
    case 5: return 13 - x;
    default: return -1;  // 若y不在1-5范围则返回-1
  }
}

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  static uint8_t hue = 0;
  // 通过x,y坐标在LED阵列上产生彩虹效果
  for (int x = 0; x < xDimension; x++) {
    for (int y = 0; y < yDimension; y++) {
      int index = calculateIndex(x + 1, y + 1);  // 因为x,y从0开始，而calculateIndex假设从1开始
      if (index != -1) {
        // 使用x坐标来改变颜色, 产生彩虹效果
        leds[index] = CHSV((8 * x + hue) % 256, 255, 255);
      }
    }
  }
  setColorForCoordinates(colorLove, Love, numLove);
  FastLED.show();
  hue++;       // 改变hue值产生动态效果
  delay(100);  // 延时以降低更新速率
}

void setColorForCoordinates(const CRGB& color, const int (*coordinates)[2], int numCoordinates) {
  for (int i = 0; i < numCoordinates; i++) {
    int index = calculateIndex(coordinates[i][0], coordinates[i][1]);
    if (index != -1) {      // 检查返回值是否表示错误
      leds[index] = color;  // 只有当没有错误时才设置LED颜色
    }
  }
}