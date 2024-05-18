#include "DHT.h"

#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11
#define LEDPIN 13     // 13

DHT dht(DHTPIN, DHTTYPE);

float initialTemperature = 0; // 存储第一次测量的温度
bool initialRead = false;     // 是否已记录初始温度
int delayTime = 3000;         // 初始延迟时间3000毫秒

void setup() {
  pinMode(LEDPIN, OUTPUT);   // 设置LED引脚为输出模式
  Serial.println(F("Start now"));
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  if (!initialRead) {
    initialTemperature = t;  // 记录第一次的温度作为基准
    initialRead = true;
  }

  digitalWrite(LEDPIN, HIGH);   // 打开LED灯
  delay(delayTime);             // 等待
  digitalWrite(LEDPIN, LOW);    // 关闭LED灯
  delay(delayTime);             // 等待

  // 根据与初始温度的差值调整延迟时间
  float temperatureDifference = t - initialTemperature; // 计算温度差
  delayTime = 3000 - (temperatureDifference * 1000);   // 基于温度差调整延迟时间
  delayTime = constrain(delayTime, 100, 10000);        // 限制延迟时间在100到10000毫秒之间

  // 输出湿度和温度
  Serial.print(F("Group 28 - Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C Delay Time: "));
  Serial.println(delayTime);
  Serial.print(f);
  Serial.print(F("°F Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
