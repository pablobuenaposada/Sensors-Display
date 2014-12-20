#include <EEPROM.h>
#include "Constants.h"
#include "Sensors.h"
#include "Led.h"
#include "Screen.h"
#include "Variables.h"
#include "Buttons.h"
#include "Speaker.h"

Constants constants;
Variables variables;
Sensors sensors;
Led led;
Buttons buttons;
Speaker speaker;
Screen screen;

void setup() {
  speaker.setStatus(true);
  speaker.speakerTone(50);
  speaker.setStatus(EEPROM.read(constants.EEPROMSPEAKER));  
  screen.initialScreen(constants.INITCOL1,constants.INITCOL2,constants.INITCOL3,constants.INITCOL4,constants.INITSTRING1,constants.INITSTRING2,constants.INITSTRING3,constants.INITSTRING4);  
  led.ledBlink(2000);
  led.ledBlink(2000);  
  screen.clear();
}

void loop() {

  checkValues();
  
  if(variables.warningScreen > 0){
    if(variables.warningScreen == 1){
      screen.bigValue(constants.SENSOR1BIG,constants.SENSOR1BIGCOL,constants.WARNINGSTRING,constants.WARNINGCOL,variables.sensor1, constants.SENSOR1UNITS);
      speaker.speakerTone(constants.SPEAKERDURATION);      
    }
    else if(variables.warningScreen == 2){
      screen.bigValue(constants.SENSOR2BIG,constants.SENSOR2BIGCOL,constants.WARNINGSTRING,constants.WARNINGCOL,variables.sensor2, constants.SENSOR2UNITS);
      speaker.speakerTone(constants.SPEAKERDURATION);
    }
    else if(variables.warningScreen == 3){
      screen.bigValue(constants.SENSOR3BIG,constants.SENSOR3BIGCOL,constants.WARNINGSTRING,constants.WARNINGCOL,variables.sensor3,constants.SENSOR3UNITS);
      speaker.speakerTone(constants.SPEAKERDURATION);
    }
  }
  
  else{
    if(variables.actualScreen == 1){
      screen.printValue(0,0,true,constants.SENSOR1NAME,variables.sensor1,true,false,constants.SENSOR1UNITS);
      screen.printValue(1,0,true,constants.SENSOR2NAME,variables.sensor2,false,true,constants.SENSOR2UNITS);
      screen.printValue(2,0,true,constants.SENSOR3NAME,variables.sensor3,true,false,constants.SENSOR3UNITS);
    }
    else if(variables.actualScreen == 2){
      screen.bigValue(constants.SENSOR1BIG,constants.SENSOR1BIGCOL,"",0,variables.sensor1,constants.SENSOR1UNITS);
    }
    else if(variables.actualScreen == 3){
      screen.bigValue(constants.SENSOR2BIG,constants.SENSOR2BIGCOL,"",0,variables.sensor2,constants.SENSOR2UNITS);
    }
    else if(variables.actualScreen == 4){
      screen.bigValue(constants.SENSOR3BIG,constants.SENSOR3BIGCOL,"",0,variables.sensor3,constants.SENSOR3UNITS);
    }
    else if(variables.actualScreen == 5){
      screen.setCursor(constants.PEAKCOL,0);
      screen.print(constants.PEAKSTRING);
      screen.printValue(1,0,true,constants.SENSOR1NAME,variables.sensor1MAX,true,false,constants.SENSOR1UNITS);
      screen.printValue(2,0,true,constants.SENSOR2NAME,variables.sensor2MAX,false,true,constants.SENSOR2UNITS);
      screen.printValue(3,0,true,constants.SENSOR3NAME,variables.sensor3MAX,true,false,constants.SENSOR3UNITS);
    }
    else if(variables.actualScreen == 6){
      screen.setCursor(constants.SETTINGSCOL,0);
      screen.print(constants.SETTINGS);
      screen.setCursor(0,1);
      screen.print("SPEAKER:");
      speaker.setStatus(EEPROM.read(constants.EEPROMSPEAKER));       
      
      if(speaker.getStatus()){
        screen.print("ON");        
      }
      else{
        screen.print("OFF");           
      }       
         
      if(variables.feature == 1){       
        if(speaker.getStatus()){          
          screen.setCursor(10,1);     
          screen.print("* ");
          if (variables.featureFlag){
            EEPROM.write(constants.EEPROMSPEAKER,0);
            variables.featureFlag=false;            
          }  
        }
        else{          
          screen.setCursor(11,1);     
          screen.print("*");
          if (variables.featureFlag){
            EEPROM.write(constants.EEPROMSPEAKER,1);  
            variables.featureFlag=false;            
          } 
        }       
      }    
      
      if(variables.feature == 2){        
        variables.featureFlag=false;
        variables.actualScreen=1;
        speaker.setStatus(EEPROM.read(constants.EEPROMSPEAKER));
        screen.settingsSaved();
      }  
    } 
    else if(variables.actualScreen == 7){
      
      screen.setCursor(constants.ALARMNAMECOL,0);
      screen.print(constants.ALARMNAME);
      
      screen.printValue(1,0,true,"OIL",EEPROM.read(constants.EEPROMSENSOR1WARNINGMIN),false,false,"");
      screen.print("|");
      screen.printValue(1,9,false,"OIL",EEPROM.read(constants.EEPROMSENSOR1WARNINGMAX),true,false,constants.SENSOR1UNITS);
      if(variables.alarmfeature == 1){
        screen.print("*");
        if(variables.alarmFlag){
          EEPROM.write(constants.EEPROMSENSOR1WARNINGMIN,EEPROM.read(constants.EEPROMSENSOR1WARNINGMIN)+1);          
          variables.alarmFlag = false;
        }
      }
      else if(variables.alarmfeature == 2){
        screen.print("*");
        if(variables.alarmFlag){
          EEPROM.write(constants.EEPROMSENSOR1WARNINGMAX,EEPROM.read(constants.EEPROMSENSOR1WARNINGMAX)+1);
          variables.alarmFlag = false;
        }
      }
      
      screen.printValue(2,0,true,"OIL",EEPROM.read(constants.EEPROMSENSOR2WARNINGMIN),false,false,"");
      screen.print("|");
      screen.printValue(2,9,false,"OIL",EEPROM.read(constants.EEPROMSENSOR2WARNINGMAX),false,false,constants.SENSOR2UNITS);
      if(variables.alarmfeature == 3){
        screen.print("*");
        if(variables.alarmFlag){
          EEPROM.write(constants.EEPROMSENSOR2WARNINGMIN,EEPROM.read(constants.EEPROMSENSOR2WARNINGMIN)+1);
          variables.alarmFlag = false;
        }
      }
      else if(variables.alarmfeature == 4){
        screen.print("*");
        if(variables.alarmFlag){
          EEPROM.write(constants.EEPROMSENSOR2WARNINGMAX,EEPROM.read(constants.EEPROMSENSOR2WARNINGMAX)+1);
          variables.alarmFlag = false;
        }
      }
      
      screen.printValue(3,0,true,"WATER",EEPROM.read(constants.EEPROMSENSOR3WARNINGMIN),false,false,"");
      screen.print("|");
      screen.printValue(3,11,false,"WATER",EEPROM.read(constants.EEPROMSENSOR3WARNINGMAX),true,false,constants.SENSOR3UNITS);
      if(variables.alarmfeature == 5){
        screen.print("*");
        if(variables.alarmFlag){
          EEPROM.write(constants.EEPROMSENSOR3WARNINGMIN,EEPROM.read(constants.EEPROMSENSOR3WARNINGMIN)+1);
          variables.alarmFlag = false;
        }
      }
      else if(variables.alarmfeature == 6){
        screen.print("*");
        if(variables.alarmFlag){
          EEPROM.write(constants.EEPROMSENSOR3WARNINGMAX,EEPROM.read(constants.EEPROMSENSOR3WARNINGMAX)+1);
          variables.alarmFlag = false;
        }
      }
      
      if(variables.alarmfeature == 7){
        variables.alarmFlag=false;
        variables.SENSOR1WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR1WARNINGMAX);
        variables.SENSOR2WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR2WARNINGMAX);
        variables.SENSOR3WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR3WARNINGMAX);
        variables.SENSOR4WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR4WARNINGMAX);
        variables.SENSOR5WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR5WARNINGMAX);
        variables.SENSOR6WARNINGMAX=EEPROM.read(constants.EEPROMSENSOR6WARNINGMAX);  
        variables.SENSOR1WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR1WARNINGMIN);
        variables.SENSOR2WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR2WARNINGMIN);
        variables.SENSOR3WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR3WARNINGMIN);
        variables.SENSOR4WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR4WARNINGMIN);
        variables.SENSOR5WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR5WARNINGMIN);
        variables.SENSOR6WARNINGMIN=EEPROM.read(constants.EEPROMSENSOR6WARNINGMIN);
        variables.actualScreen=1;
        screen.settingsSaved();
      }         
      
    }
  }
  delay(100);
}



































void checkValues(){
  variables.sensor1 = sensors.getTemp057(constants.SENSOR1);
  variables.sensor2 = sensors.getPress004(constants.SENSOR2);
  variables.sensor3 = 0;
  variables.sensor4 = 0;
  variables.sensor5 = 0;
  variables.sensor6 = 0;
    
  if (variables.sensor1 <= variables.SENSOR1WARNINGMIN){
    led.ledBlink(constants.LEDDURATION);    
    if (variables.warningScreen == -1){
      variables.warningScreen=1;
      screen.clear();
    } 
  }
  else if (variables.sensor1 >= variables.SENSOR1WARNINGMAX){
    led.ledBlink(constants.LEDDURATION);
    if (variables.warningScreen == -1){
      variables.warningScreen=1;
      screen.clear();
    }        
  }
  
  else if (variables.sensor2 <= variables.SENSOR2WARNINGMIN){
    led.ledBlink(constants.LEDDURATION);    
    if (variables.warningScreen == -1){
      variables.warningScreen=2;
      screen.clear();
    } 
  }
  else if (variables.sensor2 >= variables.SENSOR2WARNINGMAX){
    led.ledBlink(constants.LEDDURATION);
    if (variables.warningScreen == -1){
      variables.warningScreen=2;
      screen.clear();
    }        
  }
  /*
  else if (sensor3 <= SENSOR3WARNINGMIN){
    ledBlink(LEDDURATION);    
    if (warningScreen == -1){
      warningScreen=3;
      lcd.clear();
    } 
  }
  else if (sensor3 >= SENSOR3WARNINGMAX){
    ledBlink(LEDDURATION);
    if (warningScreen == -1){
      warningScreen=3;
      lcd.clear();
    }        
  }
  
  else if (sensor4 <= SENSOR4WARNINGMIN){
    ledBlink(LEDDURATION);    
    if (warningScreen == -1){
      warningScreen=4;
      lcd.clear();
    } 
  }
  else if (sensor4 >= SENSOR4WARNINGMAX){
    ledBlink(LEDDURATION);
    if (warningScreen == -1){
      warningScreen=4;
      lcd.clear();
    }        
  }
  
  else if (sensor5 <= SENSOR5WARNINGMIN){
    ledBlink(LEDDURATION);    
    if (warningScreen == -1){
      warningScreen=5;
      lcd.clear();
    } 
  }
  else if (sensor5 >= SENSOR5WARNINGMAX){
    ledBlink(LEDDURATION);
    if (warningScreen == -1){
      warningScreen=5;
      lcd.clear();
    }        
  }
  
  else if (sensor6 <= SENSOR6WARNINGMIN){
    ledBlink(LEDDURATION);    
    if (warningScreen == -1){
      warningScreen=6;
      lcd.clear();
    } 
  }
  else if (sensor6 >= SENSOR6WARNINGMAX){
    ledBlink(LEDDURATION);
    if (warningScreen == -1){
      warningScreen=6;
      lcd.clear();
    }        
  }*/
  
  else{
    if (variables.warningScreen >= 0){
      screen.clear();  //no se puede quitar?
    } 
    variables.warningScreen=-1;    
  }

  //peak values
  if (variables.sensor1 > variables.sensor1MAX){
    variables.sensor1MAX=variables.sensor1;
  }
  if (variables.sensor2 > variables.sensor2MAX){
    variables.sensor2MAX=variables.sensor2;
  }
  if (variables.sensor3 > variables.sensor3MAX){
    variables.sensor3MAX=variables.sensor3;
  }
  if (variables.sensor4 > variables.sensor4MAX){
    variables.sensor4MAX=variables.sensor4;
  }
  if (variables.sensor5 > variables.sensor5MAX){
    variables.sensor5MAX=variables.sensor5;
  }
  if (variables.sensor6 > variables.sensor6MAX){
    variables.sensor6MAX=variables.sensor6;
  }
}
















