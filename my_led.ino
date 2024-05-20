#include<led.h>
//注意，由于LED控制模块已经是标泪
LED led(2);
byte count =0;

void setup(){
Serial.begin(9600);
}

void loop(){
  if(count<10){
  led.on();
  delay(300);
  Serial.println(led.getState(),DEC);
  led.off();
  delay(300);
  Serial.println(led.getState(),DEC);
  ++count;
  if(count==10)
  led.disattach();
  }
}
