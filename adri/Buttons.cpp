#include "Buttons.h"
#include "Constants.h"
#include "Variables.h"
#include "Screen.h"
#include "Led.h"

void button1ISR(){
  Constants constants;
  Led redLed(constants.LED);
  redLed.setStatus(true);
  /*Variables variables;
  Constants constants;
  Screen screen;
  unsigned long interrupt_time = millis();
 
  if (interrupt_time - variables.last_interrupt_time > constants.DEBOUNCING){    
    if(variables.actualScreen == constants.TOTALSCREENS+1){
      variables.featureFlag=true;       
    }
    else if(variables.actualScreen == constants.TOTALSCREENS+2){
      variables.alarmFlag=true;
    }
    else if(variables.warningScreen > 0){
      variables.actualScreen=1; //cuando queremos parar el sonido de una alarma que vuelva a la pantalla 1
    }
    else{
      variables.actualScreen=variables.actualScreen+1;
      if(variables.actualScreen > constants.TOTALSCREENS){
        variables.actualScreen=1;
      }
    }    
    screen.clear();
    variables.warningScreen=0;    
  }  
  variables.last_interrupt_time = interrupt_time; */ 
}

void button2ISR(){  
  Constants constants;
  Led redLed(constants.LED);
  redLed.setStatus(false);
  /*Variables variables;
  Constants constants;
  Screen screen;
  unsigned long interrupt_time = millis();  
  
  if (interrupt_time - variables.last_interrupt_time > constants.DEBOUNCING){
    unsigned long timePressed = 0;
    while(digitalRead(constants.BUTTON2) == LOW && timePressed < constants.ALARMPRESSINGTIME){
      timePressed+=1;
      delay(1);      
    }
    
    if(timePressed >= constants.ALARMPRESSINGTIME){
      variables.actualScreen=7;
      variables.alarmfeature=1; 
    }
    else if(variables.actualScreen == constants.TOTALSCREENS+2){
      variables.alarmfeature=variables.alarmfeature+1;
    }    
    else if(variables.actualScreen == constants.TOTALSCREENS+1){
      variables.feature=variables.feature+1;    
    }
    else{
      variables.actualScreen = constants.TOTALSCREENS+1;
      variables.feature=1;
    }    
    screen.clear();
    variables.warningScreen=0;    
  }
 
  variables.last_interrupt_time = interrupt_time; */  
}

Buttons::Buttons(){
  Constants constants;
  
  pinMode(constants.BUTTON1,INPUT);
  digitalWrite(constants.BUTTON1,HIGH);
  attachInterrupt(0,button1ISR, LOW);
  
  pinMode(constants.BUTTON2,INPUT);
  digitalWrite(constants.BUTTON2,HIGH);
  attachInterrupt(1,button2ISR, LOW);  
}






