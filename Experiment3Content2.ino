// 导入TM1637和RTClib库，用于操作TM1637显示模块和DS1307实时时钟模块。
#include "TM1637.h"
#include "RTClib.h"

// 定义连接到TM1637显示模块的引脚。CLK是时钟信号线，DIO是数据信号线。
#define CLK 10
#define DIO 9

// 创建一个TM1637对象，初始化时指定CLK和DIO引脚。
TM1637 tm1637(CLK,DIO);

// 创建一个RTC_DS1307对象，用于操作DS1307实时时钟。
RTC_DS1307 RTC;
// 创建一个DateTime对象，用于存储当前时间。
DateTime theTime;
// 定义一个数组，用于显示在TM1637上，初始化为全亮（0xff表示所有段都亮）。
int8_t TimeDisp[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

// setup函数在Arduino开机后执行一次。
void setup() {
  // 初始化串口通信，设置波特率为9600。
  Serial.begin(9600);
  // 开始通信，如果找不到RTC，则输出错误信息并停止程序。
  if (!RTC.begin()) {
    Serial.println("Couldn't find RTC");
    while(1);
  }
  // 检查RTC是否运行，如果没有运行，则设置RTC的时间为编译时间。
  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  // 初始化TM1637显示模块。
  tm1637.init();
  // 设置TM1637的亮度为2（0最暗，7最亮）。
  tm1637.set(2);
  // 显示测试数字ABCD，对应的段编码是10, 11, 12, 13。
  tm1637.display(0,10);
  tm1637.display(1,11);
  tm1637.display(2,12);
  tm1637.display(3,13);
  // 延迟3000毫秒，让测试显示持续一段时间。
  delay(3000);
}

// 定义用于存储小时、分钟、秒的变量。
int hour, minute, second;
// // 用于控制TM1637上点的显示。
// unsigned char ClockPoint = 1;

// loop函数在setup执行后持续循环执行。
void loop() {
  // 从RTC获取当前时间。
  DateTime theTime = RTC.now();
  // 获取当前的小时。
  hour = theTime.hour();
  // 获取当前的秒数。
  second = theTime.second();
  // 获取当前的分钟数。
  minute = theTime.minute();

  // 将分钟和秒数拆分为单独的数字，并存入TimeDisp数组。
  TimeDisp[0] = hour / 10;
  TimeDisp[1] = hour % 10;
  TimeDisp[2] = minute / 10;
  TimeDisp[3] = minute % 10;
  TimeDisp[4] = second / 10;
  TimeDisp[5] = second % 10;
  
  // 将分解后的时间数字显示在TM1637上。
  tm1637.display(0,2);
  tm1637.display(1,8);
  tm1637.display(2,TimeDisp[2]);
  tm1637.display(3,TimeDisp[3]);
  // 在串口输出设置的时间，格式为时:分:秒。
  Serial.print("GROUP-28 ");
  Serial.print("NOW TIME:");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second);
  Serial.println();
  // // 控制显示点的开关，每次循环切换状态。
  // ClockPoint = (~ClockPoint) & 0x01;
  // if(ClockPoint)tm1637.point(POINT_ON);
  // else tm1637.point(POINT_OFF);
  tm1637.point(POINT_ON);
  // 每次更新后延迟1000毫秒。
  delay(1000);  
}
