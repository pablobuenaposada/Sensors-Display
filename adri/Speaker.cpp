#include "Speaker.h"
#include "Variables.h"
#include "Constants.h"

boolean status=true;

Speaker::Speaker(){
  Constants constants;  
  pinMode(constants.RELAY1,OUTPUT);
}

void Speaker::setStatus(boolean mode){
  status=mode;
}

boolean Speaker::getStatus(){
  return status;
}

void Speaker::speakerTone(int duration){
  Variables variables;
  Constants constants;
  if(status){
    digitalWrite(constants.RELAY1,HIGH);
    delay(duration);
    digitalWrite(constants.RELAY1,LOW);
  }
}



