#include <FastLED.h>

#define BUTTON_PIN 4
#define PUSH_KEY 12
#define DOWN_KEY 13
#define UP_KEY 14
#define LED_PIN     5
#define LED_COUNT   65  // 更改为你的灯珠数量
#define BRIGHTNESS  20 // 亮度值，范围为0-255

CRGB leds[LED_COUNT];

bool buttonStateA = HIGH;
bool lastButtonStateA = HIGH;

bool buttonStateB = HIGH;
bool lastButtonStateB = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PUSH_KEY, INPUT_PULLUP);
  pinMode(DOWN_KEY, INPUT_PULLUP);
  pinMode(UP_KEY, INPUT_PULLUP);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_COUNT);  // 配置FastLED库
  FastLED.setBrightness(BRIGHTNESS); // 设置亮度
}

void loop() {
  // int buttonState = digitalRead(BUTTON_PIN);
  // if (buttonState ==  HIGH){
  //   rainbow(); 
  // }
  // else {
  //   showLED();
  // }
  switchUI();
}

void rainbow() {
  static uint8_t hue = 0;
  fill_rainbow(leds, LED_COUNT, hue, 7);
  FastLED.show();
  delay(50);
  hue++;
}

void showLED(){
  fill_solid(leds, LED_COUNT, CHSV(0, 255, 255)); // Red in HSV format  
  FastLED.show();  
  delay(1000); 
  fill_solid(leds, LED_COUNT, CHSV(160, 255, 255)); // Blue in HSV format  
  FastLED.show();  
  delay(1000); 
}

void switchUI(){
  // 读取当前按钮状态
  buttonStateA = digitalRead(DOWN_KEY);
  buttonStateB = digitalRead(UP_KEY);

  // 功能A的按钮切换检测
  if (buttonStateA == LOW && lastButtonStateA == HIGH) {
    // 调用功能A
    rainbow();
    delay(200); // 简单的消抖延迟
  }
  
  // 功能B的按钮切换检测
  if (buttonStateB == LOW && lastButtonStateB == HIGH) {
    // 调用功能B
    showLED();
    delay(200); // 简单的消抖延迟
  }
  
  // 更新上一次按钮状态
  lastButtonStateA = buttonStateA;
  lastButtonStateB = buttonStateB;
}



#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    65
#define BRIGHTNESS  20
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// 定义多组需要常亮的灯珠的索引
const int onLEDsGroup1[] = {10, 12, 13, 15, 36, 37, 38, 39, 41, 62, 64};
const int onLEDsGroup2[] = {7, 8, 9, 16, 33,34,35,42,59,60,61};
// 你还可以定义更多组

// 一个通用函数，用于点亮指定的一组灯珠
void selectShow(const int* onLEDs, int numOnLEDs) {
  fill_solid(leds, NUM_LEDS, CRGB::Black); // 首先关闭所有灯珠
  for (int i = 0; i < numOnLEDs; i++) {
    leds[onLEDs[i]] = CRGB::Red; // 点亮指定的灯珠
  }
  FastLED.show(); // 更新显示
}

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  ledInit();
  // 初始化时选择显示某一组，例如显示第一组
}

void loop() {
}

void ledInit(){
  selectShow(onLEDsGroup1, sizeof(onLEDsGroup1) / sizeof(onLEDsGroup1[0]));
  selectShow(onLEDsGroup2, sizeof(onLEDsGroup2) / sizeof(onLEDsGroup2[0]));
}





#include <FastLED.h>

#define LED_PIN     5  // 数据线连接的Arduino引脚号
#define NUM_LEDS    65   // 灯珠的数量
#define BRIGHTNESS  255  // 最大亮度值（0-255）
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];  // 创建一个leds数组来存储每个灯珠的颜色状态

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);  // 设置全局亮度
  fill_solid(leds, NUM_LEDS, CRGB::White); // 设置所有灯珠为白色
  FastLED.show();  // 发送颜色数据到LED灯珠
}

void loop() {
  // 这里不做任何事情，所有灯珠都将持续保持白色
}




#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    65
#define BRIGHTNESS  20
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black); // 初始化所有灯珠为关闭状态
  showHello();
  
}

void loop() {
  // 这里不需要做任何事情
}

void showHello(){
  const int H_LEDs[] = {10,12,13,15,36,37,38,39,41,62,64};
  const int numH_LEDs = sizeof(H_LEDs) / sizeof(H_LEDs[0]);
  for(int i = 0; i < numH_LEDs; i++) {
    leds[H_LEDs[i]] = CRGB::Red;
  }

  FastLED.show(); // 显示设置的颜色
}

void setLedXY(int x, int y, CRGB color){
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return; // 防止数组越界
  //x=1,y=1 index = 64  x=2,y=1 index = 63  x=3,y=1 index = 62  x=4,y=1 index = 61  x=5,y=1 index = 60 ......... x=12,y=1 index = 53  x=13,y=1 index = 52
  //x=1,y=2 index = 39  x=2,y=2 index = 40  x=3,y=2 index = 41  x=4,y=2 index = 42  x=5,y=2 index = 43 ......... x=12,y=2 index = 50  x=13,y=2 index = 51
  //x=1,y=3 index = 38  x=2,y=3 index = 37  x=3,y=3 index = 36  x=4,y=3 index = 35  x=5,y=3 index = 34 ......... x=12,y=3 index = 27  x=13,y=3 index = 26
  //x=1,y=4 index = 13  x=2,y=4 index = 14  x=3,y=4 index = 15  x=4,y=4 index = 16  x=5,y=4 index = 17 ......... x=12,y=4 index = 24  x=13,y=4 index = 25
  //x=1,y=5 index = 12  x=2,y=5 index = 11  x=3,y=5 index = 10  x=4,y=5 index = 9   x=5,y=5 index = 8  ......... x=12,y=5 index = 1   x=13,y=5 index = 0
  leds[index] = color;
}




#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    65
#define BRIGHTNESS  20
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int calculateIndex(int x, int y) {
  if (x > 13 || y > 5) return -1; // 若x或y超出范围则返回-1
  
  switch (y) {
    case 1: return 65 - x;
    case 2: return 38 + x;
    case 3: return 39 - x;
    case 4: return 12 + x;
    case 5: return 13 - x;
    default: return -1; // 若y不在1-5范围则返回-1
  }
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


//---------------------------------------------------------------------------------------------------------------------------------------------------------------//
//串口测试坐标
int calculateIndex(int x, int y) {
  if (x > 13 || y > 5) return -1; // 若x或y超出范围则返回-1
  
  switch (y) {
    case 1: return 65 - x;
    case 2: return 38 + x;
    case 3: return 39 - x;
    case 4: return 12 + x;
    case 5: return 13 - x;
    default: return -1; // 若y不在1-5范围则返回-1
  }
}

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  Serial.println("Enter coordinates in the format x,y:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read the serial input until a newline character

    int commaIndex = input.indexOf(','); // Find the index of the comma
    if (commaIndex != -1 && commaIndex < input.length() - 1) {
      int x = input.substring(0, commaIndex).toInt(); // Parse the x coordinate
      int y = input.substring(commaIndex + 1).toInt(); // Parse the y coordinate

      Serial.print("Index for x=");
      Serial.print(x);
      Serial.print(", y=");
      Serial.print(y);
      Serial.print(" is: ");

      Serial.println(calculateIndex(x, y)); // Call the function and print the result
    } else {
      Serial.println("Invalid format. Please enter the coordinates in the format x,y:");
    }
  }
}

