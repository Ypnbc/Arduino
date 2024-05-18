#include "DHT.h"

#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

float initialTemperature = 0; // 存储第一次测量的温度
bool initialRead = false;     // 是否已记录初始温度
int delayTime = 10;         // 初始延迟时间3000毫秒

DHT dht(DHTPIN, DHTTYPE);

int ledPin = 9;


void setup (){
  pinMode(ledPin,OUTPUT);
  Serial.println(F("Start now"));
  Serial.begin(9600);
  dht.begin();
}

void loop(){
 float t = dht.readTemperature(); 
  

  if (isnan(t)) {
    Serial.println(F("测温失败"));
    return;
  }

  if (!initialRead) {
    initialTemperature = t;  // 记录第一次的温度作为基准
    initialRead = true;
  }

  // 根据与初始温度的差值调整延迟时间
  float temperatureDifference = t - initialTemperature; // 计算温度差
  delayTime = 10 - (temperatureDifference * 10);   // 基于温度差调整延迟时间
  delayTime = constrain(delayTime, 1, 100);        // 限制延迟时间在1到100毫秒之间

      
  for (int a=0; a<=255;a++) { //循环语句，控制PWM亮度的增加
  analogWrite(ledPin,a);
  delay(delayTime); //当前亮度级别维持的时间,单位毫秒            
  }
  for (int a=255; a>=0;a--) { //循环语句，控制PWM亮度减小
  analogWrite(ledPin,a);
  delay(delayTime); //当前亮度的维持的时间,单位毫秒  
  }

  // 输出湿度和温度
  Serial.print(F("组号:28 当前温度:  "));
  Serial.print(t);
  Serial.print(F("°C 延时: "));
  Serial.println(delayTime);
}
