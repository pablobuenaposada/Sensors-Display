#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Constants.h"
#include "Sensors.h"
#include "Screen.h"
#include "Variables.h"
#include "Led.h"
#include "Runtime.h"

Constants constants;
Variables variables;
Sensors sensors;
Screen screen;
Led redLed(constants.LED);
Runtime time;

void setup() {
  screen.init();
  openingCeremony();
  screen.clear();
  setupButtons();
  Serial.begin(9600);
}

void loop() {
  if (variables.clearLCD){ //do we need to clean the screen?
    variables.clearLCD=false;
    screen.clear();
  }
  
  checkValues();
  if (variables.actualScreen == 2) peakScreen();
  else if (variables.actualScreen == 3) setupScreen();
  else mainScreen();
  delay(constants.REFRESHRATE);
}

void mainScreen(){
  screen.printValue(0,0,true,constants.SENSOR1NAME,variables.sensor1,true,false,constants.SENSOR1UNITS);
  screen.printValue(1,0,true,constants.SENSOR2NAME,variables.sensor2,false,true,constants.SENSOR2UNITS);
  screen.printValue(2,0,true,constants.SENSOR3NAME,variables.sensor3,true,false,constants.SENSOR3UNITS);
  screen.setCursor(0,3);
  screen.print(constants.TIMENAME+": "+time.getTime());
}

void peakScreen(){
  screen.setCursor(4,0);
  screen.print(constants.PEAKNAME);
  screen.printValue(1,0,true,constants.SENSOR1NAME,variables.sensor1MAX,true,false,constants.SENSOR1UNITS);
  screen.printValue(2,0,true,constants.SENSOR2NAME,variables.sensor2MAX,false,true,constants.SENSOR2UNITS);
  screen.printValue(3,0,true,constants.SENSOR3NAME,variables.sensor3MAX,true,false,constants.SENSOR3UNITS);
}

void setupScreen(){
  screen.setCursor(constants.ALARMNAMECOL,0);
  screen.print(constants.ALARMNAME);
 
  screen.printValue(1,0,true,constants.SENSOR1NAME,EEPROM.read(constants.EEPROMSENSOR1WARNINGVALUE),true,false,constants.SENSOR1UNITS);
  screen.print(getOperatorLabel(EEPROM.read(constants.EEPROMSENSOR1WARNINGOPERATOR)));
  
  screen.printValue(2,0,true,constants.SENSOR2NAME,EEPROM.read(constants.EEPROMSENSOR2WARNINGVALUE),false,false,constants.SENSOR2UNITS);
  screen.print(getOperatorLabel(EEPROM.read(constants.EEPROMSENSOR2WARNINGOPERATOR)));

  screen.printValue(3,0,true,constants.SENSOR3NAME,EEPROM.read(constants.EEPROMSENSOR3WARNINGVALUE),true,false,constants.SENSOR3UNITS);
  screen.print(getOperatorLabel(EEPROM.read(constants.EEPROMSENSOR3WARNINGOPERATOR)));
  
  screen.setCursor(19,variables.feature/2);
  screen.print("*");
  
  if (variables.feature/2 > 3){
    variables.actualScreen=1;
    savedScreen();
  }
}

void checkValues(){
  variables.sensor1 = sensors.getTemp323057(constants.SENSORMCP1);
  variables.sensor2 = sensors.getPress360004(constants.SENSORMCP3);
  variables.sensor3 = sensors.getTemp323059(constants.SENSORMCP5);
  variables.sensor4 = 0;
  variables.sensor5 = 0;
  variables.sensor6 = 0;
  
  //peak values
  if(variables.sensor1 > variables.sensor1MAX) variables.sensor1MAX=variables.sensor1;
  if(variables.sensor2 > variables.sensor2MAX) variables.sensor2MAX=variables.sensor2;
  if(variables.sensor3 > variables.sensor3MAX) variables.sensor3MAX=variables.sensor3;
  if(variables.sensor4 > variables.sensor4MAX) variables.sensor4MAX=variables.sensor4;
  if(variables.sensor5 > variables.sensor5MAX) variables.sensor5MAX=variables.sensor5;
  if(variables.sensor6 > variables.sensor6MAX) variables.sensor6MAX=variables.sensor6;
  
  //alarm
  if(EEPROM.read(constants.EEPROMSENSOR1WARNINGOPERATOR)%2 > 0){ //greater alarm
    if(int(variables.sensor1) > EEPROM.read(constants.EEPROMSENSOR1WARNINGVALUE)) redLed.blink(constants.LEDDURATION);
  }
  else{ //smaller alarm
    if(int(variables.sensor1) < EEPROM.read(constants.EEPROMSENSOR1WARNINGVALUE)) redLed.blink(constants.LEDDURATION);
  }
  
  if(EEPROM.read(constants.EEPROMSENSOR2WARNINGOPERATOR)%2 > 0){ //greater alarm
    if(int(variables.sensor2) > EEPROM.read(constants.EEPROMSENSOR2WARNINGVALUE)) redLed.blink(constants.LEDDURATION);
  }
  else{ //smaller alarm
    if(int(variables.sensor2) < EEPROM.read(constants.EEPROMSENSOR2WARNINGVALUE)) redLed.blink(constants.LEDDURATION);
  }
  
  if(EEPROM.read(constants.EEPROMSENSOR3WARNINGOPERATOR)%2 > 0){ //greater alarm
    if(int(variables.sensor3) > EEPROM.read(constants.EEPROMSENSOR3WARNINGVALUE)) redLed.blink(constants.LEDDURATION);
  }
  else{ //smaller alarm
    if(int(variables.sensor3) < EEPROM.read(constants.EEPROMSENSOR3WARNINGVALUE)) redLed.blink(constants.LEDDURATION);
  }

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

void savedScreen(){
  Constants constants;
  screen.clear();
  screen.setCursor(constants.SETTINGSSAVEDCOL,1);
  screen.print(constants.SETTINGSSAVED);
  delay(1000);
  screen.clear();   
}

void setupButtons(){
  pinMode(constants.BUTTON1,INPUT);
  digitalWrite(constants.BUTTON1,HIGH);
  attachInterrupt(0,button1ISR, LOW);
  
  pinMode(constants.BUTTON2,INPUT);
  digitalWrite(constants.BUTTON2,HIGH);
  attachInterrupt(1,button2ISR, LOW);
}

String getOperatorLabel(int rawOperator){
  if (rawOperator%2 > 0) return "+";
  else return "-";
}

void button1ISR(){
  unsigned long interrupt_time = millis();
  if (interrupt_time - variables.last_interrupt_time > constants.DEBOUNCING){
    if (variables.actualScreen == 3){
      int sensor = variables.feature/2;
      int rawOperator = variables.feature%2;
      
      if (sensor == 1) {
        if (!rawOperator) EEPROM.write(constants.EEPROMSENSOR1WARNINGVALUE,EEPROM.read(constants.EEPROMSENSOR1WARNINGVALUE)+1);
        else EEPROM.write(constants.EEPROMSENSOR1WARNINGOPERATOR,EEPROM.read(constants.EEPROMSENSOR1WARNINGOPERATOR)+1);
      }
      else if (sensor == 2) {
        if (!rawOperator) EEPROM.write(constants.EEPROMSENSOR2WARNINGVALUE,EEPROM.read(constants.EEPROMSENSOR2WARNINGVALUE)+1);
        else EEPROM.write(constants.EEPROMSENSOR2WARNINGOPERATOR,EEPROM.read(constants.EEPROMSENSOR2WARNINGOPERATOR)+1);
      }
      else if (sensor == 3) {
        if (!rawOperator) EEPROM.write(constants.EEPROMSENSOR3WARNINGVALUE,EEPROM.read(constants.EEPROMSENSOR3WARNINGVALUE)+1);
        else EEPROM.write(constants.EEPROMSENSOR3WARNINGOPERATOR,EEPROM.read(constants.EEPROMSENSOR3WARNINGOPERATOR)+1);
      }    
    }
    else{
      variables.actualScreen = variables.actualScreen+1;
      if (variables.actualScreen > constants.TOTALSCREENS) variables.actualScreen=1;
      variables.clearLCD = true;
    }
  }
  variables.last_interrupt_time = interrupt_time;
}

void button2ISR(){
  if (variables.actualScreen == 3){
    unsigned long interrupt_time = millis();
    if (interrupt_time - variables.last_interrupt_time > constants.DEBOUNCING){
          variables.clearLCD = true;
          variables.feature += 1;
    }
    variables.last_interrupt_time = interrupt_time;
  }
  else{
    unsigned long timePressed = 0;
    while(digitalRead(constants.BUTTON2) == LOW && timePressed < constants.ALARMPRESSINGTIME){
      timePressed+=1;
      delay(1);      
     }
    
    if(timePressed >= constants.ALARMPRESSINGTIME){
      variables.actualScreen=3;
      variables.feature = 1;
      variables.clearLCD = true;
    }
  }
}















































