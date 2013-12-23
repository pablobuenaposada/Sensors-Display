#include <LiquidCrystal.h>
#include <phi_big_font.h>
#include <EEPROM.h>

//-------------------------------------
#define LED 5
#define RELAY1 4
//-------------------------------------
#define LEDDURATION 500
#define SPEAKERDURATION 100
//-------------------------------------
unsigned long last_interrupt_time=0;
//-------------------------------------
int actualScreen=1;
//-------------------------------------
boolean speaker=true;
//-------------------------------------
int feature;
boolean featureFlag;
//-------------------------------------
#define EEPROMSPEAKER 1
//-------------------------------------
#define SETTINGSSAVED "SETTINGS SAVED"
#define SETTINGSSAVEDCOL 3
#define SETTINGS "SETTINGS"
#define SETTINGSCOL 6
//-------------------------------------
#define ALARMPRESSINGTIME 1000
#define ALARMNAME "ALARM SETUP"
#define ALARMNAMECOL 4
int alarmFeature;
boolean alarmFlag;
//-------------------------------------

#define DEBOUNCING 100
#define BUTTON1 2
#define BUTTON2 3
//-------------------------------------
#define TOTALSCREENS 5
//-------------------------------------
#define INITCOL1 0
#define INITSTRING1 ""
#define INITCOL2 3
#define INITSTRING2 "RACING DISPLAY"
#define INITCOL3 5
#define INITSTRING3 "ADRI EP3"
#define INITCOL4 0
#define INITSTRING4 ""
//-------------------------------------
#define SENSOR1 A0  //VDO 150 grados
#define SENSOR2 A1 //presion 
#define SENSOR3 A2 //VDO 120 grados
#define SENSOR4 A3
#define SENSOR5 A4
#define SENSOR6 A5
//-------------------------------------
int warningScreen=-1;
//-------------------------------------
#define WARNINGSTRING "COMPTE!! PERILL!!"
#define WARNINGCOL 1
//-------------------------------------
#define PEAKSTRING "VALORS MAXIMS"
#define PEAKCOL 3
//-------------------------------------
int SENSOR1WARNINGMAX;
int SENSOR2WARNINGMAX;
int SENSOR3WARNINGMAX;
int SENSOR4WARNINGMAX;
int SENSOR5WARNINGMAX;
int SENSOR6WARNINGMAX;
int SENSOR1WARNINGMIN;
int SENSOR2WARNINGMIN;
int SENSOR3WARNINGMIN;
int SENSOR4WARNINGMIN;
int SENSOR5WARNINGMIN;
int SENSOR6WARNINGMIN;
#define EEPROMSENSOR1WARNINGMAX 2
#define EEPROMSENSOR2WARNINGMAX 3
#define EEPROMSENSOR3WARNINGMAX 4
#define EEPROMSENSOR4WARNINGMAX 5
#define EEPROMSENSOR5WARNINGMAX 6
#define EEPROMSENSOR6WARNINGMAX 7
#define EEPROMSENSOR1WARNINGMIN 8
#define EEPROMSENSOR2WARNINGMIN 9
#define EEPROMSENSOR3WARNINGMIN 10
#define EEPROMSENSOR4WARNINGMIN 11
#define EEPROMSENSOR5WARNINGMIN 12
#define EEPROMSENSOR6WARNINGMIN 13
//-------------------------------------
#define SENSOR1NAME "OLI"
#define SENSOR1UNITS "ºC"
#define SENSOR1BIG "TEMPERATURA OLI"
#define SENSOR1BIGCOL 2
#define SENSOR2NAME "OLI"
#define SENSOR2UNITS "BAR"
#define SENSOR2BIG "PRESSIO OLI"
#define SENSOR2BIGCOL 4
#define SENSOR3NAME "AIGUA"
#define SENSOR3UNITS "ºC"
#define SENSOR3BIG "TEMPERATURA AIGUA"
#define SENSOR3BIGCOL 1
#define SENSOR4NAME ""
#define SENSOR4UNITS ""
#define SENSOR5NAME ""
#define SENSOR5UNITS ""
#define SENSOR6NAME ""
#define SENSOR6UNITS ""
//------------------------------------
float sensor1=0;
float sensor2=0;
float sensor3=0;
float sensor4=0;
float sensor5=0;
float sensor6=0;
//-------------------------------------
float sensor1MAX=-999;
float sensor2MAX=-999;
float sensor3MAX=-999;
float sensor4MAX=-999;
float sensor5MAX=-999;
float sensor6MAX=-999;
//------------------------------------
LiquidCrystal lcd(13,12,11,10,9,8);
//------------------------------------

void setup() {
 
  pinMode(BUTTON1,INPUT);
  digitalWrite(BUTTON1,HIGH);
  attachInterrupt(0, button1ISR, LOW);
  
  pinMode(BUTTON2,INPUT);
  digitalWrite(BUTTON2,HIGH);
  attachInterrupt(1, button2ISR, LOW);

  pinMode(LED,OUTPUT);
  
  pinMode(RELAY1,OUTPUT);
  speaker = true;
  speakerTone(50);  
  speaker = EEPROM.read(1);    
 
  SENSOR1WARNINGMAX=EEPROM.read(EEPROMSENSOR1WARNINGMAX);
  EEPROM.write(EEPROMSENSOR2WARNINGMAX,255);
  EEPROM.write(EEPROMSENSOR3WARNINGMAX,255);
  EEPROM.write(EEPROMSENSOR4WARNINGMAX,255);
  EEPROM.write(EEPROMSENSOR5WARNINGMAX,255);
  EEPROM.write(EEPROMSENSOR6WARNINGMAX,255);  
  SENSOR1WARNINGMIN=EEPROM.read(EEPROMSENSOR1WARNINGMIN);
  EEPROM.write(EEPROMSENSOR2WARNINGMIN,0);
  EEPROM.write(EEPROMSENSOR3WARNINGMIN,0);
  EEPROM.write(EEPROMSENSOR4WARNINGMIN,0);
  EEPROM.write(EEPROMSENSOR5WARNINGMIN,0);
  EEPROM.write(EEPROMSENSOR6WARNINGMIN,0);
  
  pinMode(SENSOR1,INPUT);
  pinMode(SENSOR2,INPUT);
  pinMode(SENSOR3,INPUT);
  pinMode(SENSOR4,INPUT);
  pinMode(SENSOR5,INPUT);
  pinMode(SENSOR6,INPUT);

  lcd.begin (20,4);
  init_big_font(&lcd); 
  initialScreen(INITCOL1,INITCOL2,INITCOL3,INITCOL4,INITSTRING1,INITSTRING2,INITSTRING3,INITSTRING4);  
  //checkered();
  
  ledBlink(2000);
  ledBlink(2000);  
  lcd.clear();
}

void loop() {

  checkValues();
  
  if(warningScreen > 0){
    if(warningScreen == 1){
      bigValue(SENSOR1BIG,SENSOR1BIGCOL,WARNINGSTRING,WARNINGCOL,sensor1, SENSOR1UNITS);
      speakerTone(SPEAKERDURATION);      
    }
    else if(warningScreen == 2){
      bigValue(SENSOR2BIG,SENSOR2BIGCOL,WARNINGSTRING,WARNINGCOL,sensor2, SENSOR2UNITS);
      speakerTone(SPEAKERDURATION);
    }
    else if(warningScreen == 3){
      bigValue(SENSOR3BIG,SENSOR3BIGCOL,WARNINGSTRING,WARNINGCOL,sensor3, SENSOR3UNITS);
      speakerTone(SPEAKERDURATION);
    }
  }
  
  else{
    if(actualScreen == 1){
      printValue(0,0,true,SENSOR1NAME,sensor1,true,false,SENSOR1UNITS);
      printValue(0,10,false,SENSOR2NAME,sensor2,false,true,SENSOR2UNITS);
      printValue(1,0,true,SENSOR3NAME,sensor3,true,false,SENSOR3UNITS);
    }
    else if(actualScreen == 2){
      bigValue(SENSOR1BIG,SENSOR1BIGCOL,"",0,sensor1,SENSOR1UNITS);
    }
    else if(actualScreen == 3){
      bigValue(SENSOR2BIG,SENSOR2BIGCOL,"",0,sensor2,SENSOR2UNITS);
    }
    else if(actualScreen == 4){
      bigValue(SENSOR3BIG,SENSOR3BIGCOL,"",0,sensor3,SENSOR3UNITS);
    }
    else if(actualScreen == 5){
      lcd.setCursor(PEAKCOL,0);
      lcd.print(PEAKSTRING);
      printValue(1,0,true,SENSOR1NAME,sensor1MAX,true,false,SENSOR1UNITS);
      printValue(1,10,false,SENSOR2NAME,sensor2MAX,false,true,SENSOR2UNITS);
      printValue(2,0,true,SENSOR3NAME,sensor3MAX,true,false,SENSOR3UNITS);
    }
    else if(actualScreen == 6){
      lcd.setCursor(SETTINGSCOL,0);
      lcd.print(SETTINGS);
      lcd.setCursor(0,1);
      lcd.print("SPEAKER:");
      speaker = EEPROM.read(EEPROMSPEAKER);       
      
      if(speaker){
        lcd.print("ON");        
      }
      else{
        lcd.print("OFF");           
      }       
         
      if(feature == 1){       
        if(speaker){          
          lcd.setCursor(10,1);     
          lcd.print("* ");
          if (featureFlag){
            EEPROM.write(EEPROMSPEAKER,0);            
            featureFlag=false;            
          }  
        }
        else{          
          lcd.setCursor(11,1);     
          lcd.print("*");
          if (featureFlag){
            EEPROM.write(EEPROMSPEAKER,1);            
            featureFlag=false;            
          } 
        }       
      }    
      
      if(feature == 2){        
        featureFlag=false;
        actualScreen=1;
        settingsSaved();
      }  
    } 
    else if(actualScreen == 7){
      
      lcd.setCursor(ALARMNAMECOL,0);
      lcd.print(ALARMNAME);
      
      printValue(1,0,true,SENSOR1NAME,EEPROM.read(EEPROMSENSOR1WARNINGMIN),false,false,"");
      lcd.print("|");
      printValue(1,9,false,SENSOR1NAME,EEPROM.read(EEPROMSENSOR1WARNINGMAX),true,false,SENSOR1UNITS);
      if(alarmFeature == 1){
        lcd.print("*");
        if(alarmFlag){
          EEPROM.write(EEPROMSENSOR1WARNINGMIN,EEPROM.read(EEPROMSENSOR1WARNINGMIN)+1);
          alarmFlag = false;
        }
      }
      else if(alarmFeature == 2){
        lcd.print("*");
        if(alarmFlag){
          EEPROM.write(EEPROMSENSOR1WARNINGMAX,EEPROM.read(EEPROMSENSOR1WARNINGMAX)+1);
          alarmFlag = false;
        }
      }
      
      printValue(2,0,true,SENSOR2NAME,EEPROM.read(EEPROMSENSOR2WARNINGMIN),false,false,"");
      lcd.print("|");
      printValue(2,9,false,SENSOR2NAME,EEPROM.read(EEPROMSENSOR2WARNINGMAX),false,false,SENSOR2UNITS);
      if(alarmFeature == 3){
        lcd.print("*");
        if(alarmFlag){
          EEPROM.write(EEPROMSENSOR2WARNINGMIN,EEPROM.read(EEPROMSENSOR2WARNINGMIN)+1);
          alarmFlag = false;
        }
      }
      else if(alarmFeature == 4){
        lcd.print("*");
        if(alarmFlag){
          EEPROM.write(EEPROMSENSOR2WARNINGMAX,EEPROM.read(EEPROMSENSOR2WARNINGMAX)+1);
          alarmFlag = false;
        }
      }
      
      printValue(3,0,true,SENSOR3NAME,EEPROM.read(EEPROMSENSOR3WARNINGMIN),false,false,"");
      lcd.print("|");
      printValue(3,11,false,SENSOR3NAME,EEPROM.read(EEPROMSENSOR3WARNINGMAX),true,false,SENSOR3UNITS);
      if(alarmFeature == 5){
        lcd.print("*");
        if(alarmFlag){
          EEPROM.write(EEPROMSENSOR3WARNINGMIN,EEPROM.read(EEPROMSENSOR3WARNINGMIN)+1);
          alarmFlag = false;
        }
      }
      else if(alarmFeature == 6){
        lcd.print("*");
        if(alarmFlag){
          EEPROM.write(EEPROMSENSOR3WARNINGMAX,EEPROM.read(EEPROMSENSOR3WARNINGMAX)+1);
          alarmFlag = false;
        }
      }
      
      if(alarmFeature == 7){
        alarmFlag=false;
        actualScreen=1;
        settingsSaved();
      }         
      
    }
  }
  delay(100);
}






























void settingsSaved(){
  lcd.clear();
  lcd.setCursor(SETTINGSSAVEDCOL,1);
  lcd.print(SETTINGSSAVED);
  delay(1000);
  lcd.clear();   
}

void printValue(int row, int col, boolean title, String name, int value, boolean degree, boolean decimal, String unit){
  String values="";
  if(title){
    values.concat(name+String(": "));
  }
  if (value < 0){
    if(value > -10){
      values.concat(" ");
    }
  }
  else if(value < 10){
    values.concat("  ");
  }
  else if(value < 100){
    values.concat(" ");
  }
  
  if(decimal){
    char floatString[10];
    dtostrf(value,1,2,floatString);
    values.concat(floatString);    
  }
  else{
    values.concat(value);
  }
  
  if(unit.substring(0,2) == "º"){
    values.concat((char)223);
    values.concat(unit.substring(2));
  }  
  else{
    values.concat(unit);
  }  
    
  lcd.setCursor(col,row);
  lcd.print(values);
} 

void initialScreen(int col1, int col2, int col3, int col4, String string1, String string2, String string3, String string4){
  lcd.setCursor(col1,0);
  lcd.print(string1);
  lcd.setCursor(col2,1);
  lcd.print(string2);
  lcd.setCursor(col3,2);
  lcd.print(string3);
  lcd.setCursor(col4,3);
  lcd.print(string4);
}

void checkValues(){
  sensor1 = voltage2temp(getSensorVoltage(SENSOR1));
  sensor2 = voltage2pressure(getSensorVoltage(SENSOR2));
  sensor3 = voltage2temp2(getSensorVoltage(SENSOR3));
  sensor4 = getSensorVoltage(SENSOR4);
  sensor5 = getSensorVoltage(SENSOR5);
  sensor6 = getSensorVoltage(SENSOR6);
    
  if (sensor1 <= SENSOR1WARNINGMIN){
    ledBlink(LEDDURATION);    
    if (warningScreen == -1){
      warningScreen=1;
      lcd.clear();
    } 
  }
  else if (sensor1 >= SENSOR1WARNINGMAX){
    ledBlink(LEDDURATION);
    if (warningScreen == -1){
      warningScreen=1;
      lcd.clear();
    }        
  }
  
  /*else if (sensor2 <= SENSOR2WARNINGMIN){
    ledBlink(LEDDURATION);    
    if (warningScreen == -1){
      warningScreen=2;
      lcd.clear();
    } 
  }
  else if (sensor2 >= SENSOR2WARNINGMAX){
    ledBlink(LEDDURATION);
    if (warningScreen == -1){
      warningScreen=2;
      lcd.clear();
    }        
  }
  
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
    if (warningScreen >= 0){
      lcd.clear();  //no se puede quitar?
    } 
    warningScreen=-1;    
  }

  //peak values
  if (sensor1 > sensor1MAX){
    sensor1MAX=sensor1;
  }
  if (sensor2 > sensor2MAX){
    sensor2MAX=sensor2;
  }
  if (sensor3 > sensor3MAX){
    sensor3MAX=sensor3;
  }
  if (sensor4 > sensor4MAX){
    sensor4MAX=sensor4;
  }
  if (sensor5 > sensor5MAX){
    sensor5MAX=sensor5;
  }
  if (sensor6 > sensor6MAX){
    sensor6MAX=sensor6;
  }
}

//for VDO 323-057 150º celsius with voltage divider of 220ohms
float voltage2temp(float voltage){  
  return -0.05007201037*pow(voltage,10) + 1.171260711*pow(voltage,9) - 11.55461723*pow(voltage,8) + 62.20510364*pow(voltage,7) - 196.4010868*pow(voltage,6) + 356.468504*pow(voltage,5) - 305.3996258*pow(voltage,4) - 57.02805328*pow(voltage,3) + 378.5236931*pow(voltage,2) - 366.4523339*voltage + 243.2379721;
}

//for VDO 120ºC 220ohms
float voltage2temp2(float voltage){
  return -1.961719594*pow(10,-2)*pow(voltage,10) + 4.365134798*pow(10,-1)*pow(voltage,9) - 4.007999271*pow(voltage,8) + 19.16675735*pow(voltage,7) - 47.41629982*pow(voltage,6) + 35.44696617*pow(voltage,5) + 117.1601486*pow(voltage,4) - 370.2963848*pow(voltage,3) + 474.9815884*pow(voltage,2) - 347.2521348*voltage + 209.8279558;
}

//for M10 VDO 360-081-029-010 pressure sender 10 BAR and voltage divier with 220ohms
float voltage2pressure(float voltage){
  return 0.345207949*pow(voltage,8) - 3.597256695*pow(voltage,7) + 15.88816089*pow(voltage,6) - 38.43159587*pow(voltage,5) + 55.09001405*pow(voltage,4) - 46.88577533*pow(voltage,3) + 23.34568903*pow(voltage,2) - 3.67372459*voltage + 0.07053106278;
}

float getSensorVoltage(int sensor){
  return (analogRead(sensor)/1024.000)*5;
}

void ledBlink(int delayTime){
  for(int i=0; i <= 255; i++){
    analogWrite(LED,i);
    delayMicroseconds(delayTime);
  }
  for(int i=255; i >=0 ; i--){
    analogWrite(LED,i);
    delayMicroseconds(delayTime);
  }  
}

void speakerTone(int duration){
  if(speaker){
    digitalWrite(RELAY1,HIGH);
    delay(duration);
    digitalWrite(RELAY1,LOW);
  }
}

void bigValue(String title, int colTitle,String subTitle, int colSubtitle, int value, String units){ 
  lcd.setCursor(colTitle,0);
  lcd.print(title);  

  String stringValue;
  if(value < 10){
    stringValue = "00"+String(value);
  }
  else if(value < 100){
    stringValue = "0"+String(value);
  }  
  else{
    stringValue = String(value);
  }
  char charBuf[4];
  stringValue.toCharArray(charBuf, 4);
  render_big_msg(charBuf,3,1);

  if(units.substring(0,2) == "º"){
    lcd.setCursor(15,2);
    lcd.write(0b11011111); 
    lcd.setCursor(16,2);  
    lcd.print(units.substring(2,3));  
  }
  else{
    lcd.setCursor(15,2);
    lcd.print(units); 
  }  

  lcd.setCursor(colSubtitle,3);
  lcd.print(subTitle);
}

byte customChar[8] = {
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111
};

/*void checkered(){
  lcd.createChar(0, customChar);
  for(int i=0; i< 20; i=i+2){
    for(int j=0; j<4; j++){
      lcd.setCursor(i+j%2,j);
      lcd.write((uint8_t)0);
      lcd.setCursor((i+j%2)+1,j);
      lcd.print(" ");  
    }
    
  }
}*/

void button1ISR(){
  unsigned long interrupt_time = millis();  
  if (interrupt_time - last_interrupt_time > DEBOUNCING){
    if(actualScreen == TOTALSCREENS+1){
      featureFlag=true;       
    }
    else if(actualScreen == TOTALSCREENS+2){
      alarmFlag=true;
    }
    else if(warningScreen > 0){
      actualScreen=1; //cuando queremos parar el sonido de una alarma que vuelva a la pantalla 1
    }
    else{
      actualScreen=actualScreen+1;
      if(actualScreen > TOTALSCREENS){
        actualScreen=1;
      }
    }    
    lcd.clear();
    warningScreen=0;    
  }  
  last_interrupt_time = interrupt_time;  
}

void button2ISR(){  
  unsigned long interrupt_time = millis();  
  if (interrupt_time - last_interrupt_time > DEBOUNCING){ 
    unsigned long timePressed = 0;
    while(digitalRead(BUTTON2) == LOW && timePressed < ALARMPRESSINGTIME){
      timePressed+=1;
      delay(1);      
    }
    
    if(timePressed >= ALARMPRESSINGTIME){
      actualScreen=7;
      alarmFeature=1; 
    }
    else if(actualScreen == TOTALSCREENS+2){
      alarmFeature=alarmFeature+1;
    }    
    else if(actualScreen == TOTALSCREENS+1){
      feature=feature+1;    
    }
    else{
      actualScreen = TOTALSCREENS+1;
      feature=1;
    }    
    lcd.clear();
    warningScreen=0;    
  }
  
  last_interrupt_time = interrupt_time;   
}

