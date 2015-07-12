#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Constants.h"
#include "Sensors.h"
#include "Screen.h"
#include "Variables.h"

Constants constants;
Variables variables;
Sensors sensors;
Screen screen;

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
  variables.sensor1 = sensors.getTemp057(constants.SENSORMCP1);
  variables.sensor2 = sensors.getPress004(constants.SENSORMCP3);
  variables.sensor3 = sensors.getTemp057(constants.SENSORMCP5);
  variables.sensor4 = 0;
  variables.sensor5 = 0;
  variables.sensor6 = 0;
}

void openingCeremony(){
  screen.backlight(true);
  delay(250);
  screen.backlight(false);
  delay(250);
  screen.backlight(true);
  delay(250);
  screen.backlight(false);
  delay(250);
  screen.backlight(true);
  screen.initialScreen(constants.INITCOL1,constants.INITCOL2,constants.INITCOL3,constants.INITCOL4,constants.INITSTRING1,constants.INITSTRING2,constants.INITSTRING3,constants.INITSTRING4);
  delay(5000);  
}














































