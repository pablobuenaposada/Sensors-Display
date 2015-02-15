#include <EEPROM.h>
#include "Constants.h"

void setup(){
  Constants constants;
  EEPROM.write(constants.EEPROMSENSOR1WARNINGMAX,120);
  EEPROM.write(constants.EEPROMSENSOR1WARNINGMIN,0);

  EEPROM.write(constants.EEPROMSENSOR2WARNINGMAX,10);
  EEPROM.write(constants.EEPROMSENSOR2WARNINGMIN,2);
  
  EEPROM.write(constants.EEPROMSENSOR3WARNINGMAX,0); 
  EEPROM.write(constants.EEPROMSENSOR3WARNINGMIN,0);
  
  EEPROM.write(constants.EEPROMSENSOR4WARNINGMAX,2);
  EEPROM.write(constants.EEPROMSENSOR5WARNINGMAX,0);
  EEPROM.write(constants.EEPROMSENSOR6WARNINGMAX,0);  
  

  EEPROM.write(constants.EEPROMSENSOR4WARNINGMIN,0);
  EEPROM.write(constants.EEPROMSENSOR5WARNINGMIN,0);
  EEPROM.write(constants.EEPROMSENSOR6WARNINGMIN,0);
}

void loop(){
}
