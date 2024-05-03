#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // 设置DS3231的时间到当前编译时间
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // 如果要设置特定的日期和时间，可以使用下面的方法：
    rtc.adjust(DateTime(2024, 5, 3, 22, 44, 0));
  }

  // 初始化I2C
  Wire.begin(22, 21); // SDA, SCL 如果你使用的不是默认引脚，进行相应的更改
}

void loop() {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(1000);
}