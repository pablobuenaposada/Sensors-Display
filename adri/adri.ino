#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Constants.h"
#include "Sensors.h"
#include "Screen.h"
#include "Variables.h"
#include "Led.h"
#include "Buttons.h"

Constants constants;
Variables variables;
Sensors sensors;
Screen screen;
Led redLed(constants.LED);
Buttons buttons;

void setup() {
  screen.init();
  openingCeremony();
  screen.clear();
}

void loop() {
  checkValues(); 
  screen.printValue(0,0,true,constants.SENSOR1NAME,variables.sensor1,true,false,constants.SENSOR1UNITS);
  screen.printValue(1,0,true,constants.SENSOR2NAME,variables.sensor2,false,true,constants.SENSOR2UNITS);
  screen.printValue(2,0,true,constants.SENSOR3NAME,variables.sensor3,true,false,constants.SENSOR3UNITS);
  delay(constants.REFRESHRATE);
}

void checkValues(){
  variables.sensor1 = sensors.getTemp323057(constants.SENSORMCP1);
  variables.sensor2 = sensors.getPress360004(constants.SENSORMCP3);
  variables.sensor3 = sensors.getTemp323059(constants.SENSORMCP5);
  variables.sensor4 = 0;
  variables.sensor5 = 0;
  variables.sensor6 = 0;
}

void openingCeremony(){
  uint8_t e[8] = {0x1f, 0x11, 0x17, 0x17, 0x13, 0x17, 0x11, 0x1f};
  uint8_t p[8] = {0x1f, 0x11, 0x15, 0x15, 0x11, 0x17, 0x17, 0x1f};
  uint8_t three[8] = {0x1f, 0x13, 0x1d, 0x1d, 0x11, 0x1d, 0x13, 0x1f};
  screen.storeCustomChar(0,e);
  screen.storeCustomChar(1,p);
  screen.storeCustomChar(2,three);
  screen.initialScreen(constants.INITCOL1,constants.INITCOL2,constants.INITCOL3,constants.INITCOL4,constants.INITSTRING1,constants.INITSTRING2,constants.INITSTRING3,constants.INITSTRING4);
  screen.setCursor(10,2);
  screen.printCustomChar(0);
  screen.printCustomChar(1);
  screen.printCustomChar(2);
  for(int i=0; i <= 2; i++) redLed.fade(15);
  screen.backlight(false);
  delay(250);
  screen.backlight(true);
}














































