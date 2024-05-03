#include <FastLED.h>
#include "location.h"
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

#define LED_PIN 5
#define NUM_LEDS 65
#define BRIGHTNESS 20
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

const CRGB colorPoint = CRGB(255, 255, 255);  // 定义白色
const int point[][2] = { { 7, 2 }, { 7, 4 } };
const int numNubmerPoint = sizeof(point) / sizeof(point[0]);  // 计算坐标点数量

const CRGB colorZero = CRGB(255, 255, 255);  // 定义白色
const int firstNumberZero[][2] = { { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 2, 1 }, { 2, 5 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } };
const int secondNumberZero[][2] = { { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 5, 1 }, { 5, 5 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 } };
const int thirdNumberZero[][2] = { { 8, 1 }, { 8, 2 }, { 8, 3 }, { 8, 4 }, { 8, 5 }, { 9, 1 }, { 9, 5 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 4 }, { 10, 5 } };
const int fourthNumberZero[][2] = { { 11, 1 }, { 11, 2 }, { 11, 3 }, { 11, 4 }, { 11, 5 }, { 12, 1 }, { 12, 5 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 } };
const int numNumberZero = sizeof(firstNumberZero) / sizeof(firstNumberZero[0]);  // 计算坐标点数量

const CRGB colorOne = CRGB::Red;  // 定义灯光颜色
const int firstNumberOne[][2] = { { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } };
const int secondNumberOne[][2] = { { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 } };
const int thirdNumberOne[][2] = { { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 4 }, { 10, 5 } };
const int fourthNumberOne[][2] = { { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 } };
const int numNumberOne = sizeof(firstNumberOne) / sizeof(firstNumberOne[0]);  // 计算坐标点数量

const CRGB colorTwo = CRGB(255, 165, 0);  // 定义橙色
const int firstNumberTwo[][2] = { { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 5 }, { 1, 2 }, { 2, 1 }, { 2, 3 }, { 2, 5 }, { 3, 1 }, { 3, 3 }, { 3, 4 }, { 3, 5 } };
const int secondNumberTwo[][2] = { { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 5 }, { 4, 2 }, { 5, 1 }, { 5, 3 }, { 5, 5 }, { 6, 1 }, { 6, 3 }, { 6, 4 }, { 6, 5 } };
const int thirdNumberTwo[][2] = { { 8, 1 }, { 8, 2 }, { 8, 3 }, { 8, 5 }, { 8, 2 }, { 9, 1 }, { 9, 3 }, { 9, 5 }, { 10, 1 }, { 10, 3 }, { 10, 4 }, { 10, 5 } };
const int fourthNumberTwo[][2] = { { 11, 1 }, { 11, 2 }, { 11, 3 }, { 11, 5 }, { 11, 2 }, { 12, 1 }, { 12, 3 }, { 12, 5 }, { 13, 1 }, { 13, 3 }, { 13, 4 }, { 13, 5 } };
const int numNumberTwo = sizeof(firstNumberTwo) / sizeof(firstNumberTwo[0]);  // 计算坐标点数量

const CRGB colorThree = CRGB(0, 255, 0);  // 定义绿色
const int firstNumberThree[][2] = { { 1, 1 }, { 1, 3 }, { 1, 5 }, { 2, 1 }, { 2, 3 }, { 2, 5 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } };
const int secondNumberThree[][2] = { { 4, 1 }, { 4, 3 }, { 4, 5 }, { 5, 1 }, { 5, 3 }, { 5, 5 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 } };
const int thirdNumberThree[][2] = { { 8, 1 }, { 8, 3 }, { 8, 5 }, { 9, 1 }, { 9, 3 }, { 9, 5 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 4 }, { 10, 5 } };
const int fourthNumberThree[][2] = { { 11, 1 }, { 11, 3 }, { 11, 5 }, { 12, 1 }, { 12, 3 }, { 12, 5 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 } };
const int numNumberThree = sizeof(firstNumberThree) / sizeof(firstNumberThree[0]);  // 计算坐标点数量

const CRGB colorFour = CRGB(255, 255, 0);  // 定义黄色
const int firstNumberFour[][2] = { { 1, 3 }, { 1, 4 }, { 1, 5 }, { 2, 3 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } };
const int secondNumberFour[][2] = { { 4, 3 }, { 4, 4 }, { 4, 5 }, { 5, 3 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 } };
const int thirdNumberFour[][2] = { { 8, 3 }, { 8, 4 }, { 8, 5 }, { 9, 3 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 4 }, { 10, 5 } };
const int fourthNumberFour[][2] = { { 11, 3 }, { 11, 4 }, { 11, 5 }, { 12, 3 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 } };
const int numNumberFour = sizeof(firstNumberFour) / sizeof(firstNumberFour[0]);  // 计算坐标点数量

const CRGB colorFive = CRGB(0, 255, 255);  // 定义青色
const int firstNumberFive[][2] = { { 1, 1 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 2, 1 }, { 2, 3 }, { 2, 5 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 5 } };
const int secondNumberFive[][2] = { { 4, 1 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 5, 1 }, { 5, 3 }, { 5, 5 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 5 } };
const int thirdNumberFive[][2] = { { 8, 1 }, { 8, 3 }, { 8, 4 }, { 8, 5 }, { 9, 1 }, { 9, 3 }, { 9, 5 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 5 } };
const int fourthNumberFive[][2] = { { 11, 1 }, { 11, 3 }, { 11, 4 }, { 11, 5 }, { 12, 1 }, { 12, 3 }, { 12, 5 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 5 } };
const int numNumberFive = sizeof(firstNumberFive) / sizeof(firstNumberFive[0]);  // 计算坐标点数量

const CRGB colorSix = CRGB(0, 255, 255);  // 定义青色
const int firstNumberSix[][2] = { { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 2, 1 }, { 2, 3 }, { 2, 5 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 5 } };
const int secondNumberSix[][2] = { { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 5, 1 }, { 5, 3 }, { 5, 5 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 5 } };
const int thirdNumberSix[][2] = { { 8, 1 }, { 8, 2 }, { 8, 3 }, { 8, 4 }, { 8, 5 }, { 9, 1 }, { 9, 3 }, { 9, 5 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 5 } };
const int fourthNumberSix[][2] = { { 11, 1 }, { 11, 2 }, { 11, 3 }, { 11, 4 }, { 11, 5 }, { 12, 1 }, { 12, 3 }, { 12, 5 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 5 } };
const int numNumberSix = sizeof(firstNumberSix) / sizeof(firstNumberSix[0]);  // 计算坐标点数量

const CRGB colorSeven = CRGB(0, 255, 255);  // 定义青色
const int firstNumberSeven[][2] = { { 1, 5 }, { 2, 5 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } };
const int secondNumberSeven[][2] = { { 4, 5 }, { 5, 5 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 } };
const int thirdNumberSeven[][2] = { { 8, 5 }, { 9, 5 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 4 }, { 10, 5 } };
const int fourthNumberSeven[][2] = { { 11, 5 }, { 12, 5 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 } };
const int numNumberSeven = sizeof(firstNumberSeven) / sizeof(firstNumberSeven[0]);  // 计算坐标点数量

const CRGB colorEight = CRGB(255, 105, 180);  // 定义粉色
const int firstNumberEight[][2] = { { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 2, 1 }, { 2, 3 }, { 2, 5 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } };
const int secondNumberEight[][2] = { { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 5, 1 }, { 5, 3 }, { 5, 5 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 } };
const int thirdNumberEight[][2] = { { 8, 1 }, { 8, 2 }, { 8, 3 }, { 8, 4 }, { 8, 5 }, { 9, 1 }, { 9, 3 }, { 9, 5 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 4 }, { 10, 5 } };
const int fourthNumberEight[][2] = { { 11, 1 }, { 11, 2 }, { 11, 3 }, { 11, 4 }, { 11, 5 }, { 12, 1 }, { 12, 3 }, { 12, 5 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 } };
const int numNumberEight = sizeof(firstNumberEight) / sizeof(firstNumberEight[0]);  // 计算坐标点数量

const CRGB colorNine = CRGB(139, 69, 19);  // 定义棕色
const int firstNumberNine[][2] = { { 1, 1 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 2, 1 }, { 2, 3 }, { 2, 5 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } };
const int secondNumberNine[][2] = { { 4, 1 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 5, 1 }, { 5, 3 }, { 5, 5 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 } };
const int thirdNumberNine[][2] = { { 8, 1 }, { 8, 3 }, { 8, 4 }, { 8, 5 }, { 9, 1 }, { 9, 3 }, { 9, 5 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 4 }, { 10, 5 } };
const int fourthNumberNine[][2] = { { 11, 1 }, { 11, 3 }, { 11, 4 }, { 11, 5 }, { 12, 1 }, { 12, 3 }, { 12, 5 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 } };
const int numNumberNine = sizeof(firstNumberNine) / sizeof(firstNumberNine[0]);  // 计算坐标点数量

int calculateIndex(int x, int y) {
  if (x > 13 || y > 5) return -1;  // 若x或y超出范围则返回-1

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
  Wire.begin(22, 21);
  showLED();
}

void loop() {
  static int currentColorIndex = 0;                                         // 当前颜色的索引
  blinkCoordinates(colorPoint, point, numNubmerPoint, 500); // 500为闪烁间隔时间（毫秒）
  delay(500);                                                      // 延时以便看到闪烁效果

  // int first, second, third, fourth;
  // getTimeAndCheck(&first, &second, &third, &fourth);
  
}

void setColorForCoordinates(const CRGB& color, const int (*coordinates)[2], int numCoordinates) {
  for (int i = 0; i < numCoordinates; i++) {
    int index = calculateIndex(coordinates[i][0], coordinates[i][1]);
    if (index != -1) {      // 检查返回值是否表示错误
      leds[index] = color;  // 只有当没有错误时才设置LED颜色
    }
  }
}

void showLED() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  setColorForCoordinates(colorNine, firstNumberNine, numNumberNine);
  setColorForCoordinates(colorNine, secondNumberNine, numNumberNine);
  setColorForCoordinates(colorNine, thirdNumberNine, numNumberNine);
  setColorForCoordinates(colorNine, fourthNumberNine, numNumberNine);
  FastLED.show();
}

void blinkCoordinates(const CRGB& color, const int (*coordinates)[2], int numCoordinates, unsigned long interval) {
  static unsigned long lastBlinkTime = 0; // 上次闪烁的时间戳
  static bool isOn = true; // 闪烁状态标记
  
  unsigned long currentTime = millis(); // 当前时间戳
  
  if (currentTime - lastBlinkTime > interval) {
    lastBlinkTime = currentTime; // 更新上次闪烁时间
    if (isOn) {
      // 若当前是亮着的，将灯珠颜色设置为黑色（熄灭状态）
      setColorForCoordinates(CRGB::Black, coordinates, numCoordinates);
    } else {
      // 否则将灯珠颜色设置为指定颜色（亮起状态）
      setColorForCoordinates(color, coordinates, numCoordinates);
    }
    isOn = !isOn; // 改变闪烁状态
    FastLED.show(); // 更新灯珠状态
  }
}

void getTimeAndCheck(int *firstNum, int *secondNum, int *thirdNum, int *fourthNum){
  DateTime now = rtc.now();
  int hour = now.hour();
  int minute = now.minute();
  
  // 计算小时数的第一位和第二位数字
  *firstNum = hour / 10;  // 获得小时的第一位数
  *secondNum = hour % 10;  // 获得小时的第二位数

  // 计算分钟数的第一位和第二位数字
  *thirdNum = minute / 10;  // 获得分钟的第一位数
  *fourthNum = minute % 10;  // 获得分钟的第二位数
}