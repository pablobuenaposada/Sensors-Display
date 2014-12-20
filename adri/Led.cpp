#include "Led.h"
#include "Constants.h"

Led::Led(){
  Constants constants;
  pinMode(constants.LED,OUTPUT);
}

void Led::ledBlink(int delayTime){
  Constants constants;
  for(int i=0; i <= 255; i++){
    analogWrite(constants.LED,i);
    delayMicroseconds(delayTime);
  }
  for(int i=255; i >=0 ; i--){
    analogWrite(constants.LED,i);
    delayMicroseconds(delayTime);
  }  
}

