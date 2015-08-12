#include "Variables.h"
#include "Constants.h"
#include <EEPROM.h>


Variables::Variables(){
  Constants constants;
  SENSOR1WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR1WARNINGMAX);
  SENSOR2WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR2WARNINGMAX);
  SENSOR3WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR3WARNINGMAX);
  SENSOR4WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR4WARNINGMAX);
  SENSOR5WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR5WARNINGMAX);
  SENSOR6WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR6WARNINGMAX);  
  SENSOR1WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR1WARNINGMIN);
  SENSOR2WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR2WARNINGMIN);
  SENSOR3WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR3WARNINGMIN);
  SENSOR4WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR4WARNINGMIN);
  SENSOR5WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR5WARNINGMIN);
  SENSOR6WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR6WARNINGMIN);
}

int Variables::actualScreen=1;
unsigned long Variables::last_interrupt_time=0;
int Variables::feature;
boolean Variables::featureFlag;
int Variables::alarmfeature;
boolean Variables::alarmFlag;
int Variables::warningScreen=-1;
int Variables::SENSOR1WARNINGMAX;
int Variables::SENSOR2WARNINGMAX;
int Variables::SENSOR3WARNINGMAX;
int Variables::SENSOR4WARNINGMAX;
int Variables::SENSOR5WARNINGMAX;
int Variables::SENSOR6WARNINGMAX;
int Variables::SENSOR1WARNINGMIN;
int Variables::SENSOR2WARNINGMIN;
int Variables::SENSOR3WARNINGMIN;
int Variables::SENSOR4WARNINGMIN;
int Variables::SENSOR5WARNINGMIN;
int Variables::SENSOR6WARNINGMIN;
float Variables::sensor1=0;
float Variables::sensor2=0;
float Variables::sensor3=0;
float Variables::sensor4=0;
float Variables::sensor5=0;
float Variables::sensor6=0;
float Variables::sensor1MAX=-999;
float Variables::sensor2MAX=-999;
float Variables::sensor3MAX=-999;
float Variables::sensor4MAX=-999;
float Variables::sensor5MAX=-999;
float Variables::sensor6MAX=-999;

boolean Variables::clearLCD=false;
