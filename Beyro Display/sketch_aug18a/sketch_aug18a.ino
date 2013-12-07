#include <LiquidCrystal.h>
#include <phi_big_font.h>

#define SENSOR1 A0  //VDO 150 grados
#define SENSOR2 A1 //presion 
#define SENSOR3 A2 //VDO 120 grados
#define SENSOR4 A3
#define SENSOR5 A4
#define SENSOR6 A5

#define LED 5

#define DEBOUNCING 100
#define BUTTON1 2
#define TOTALSCREENS 5

#define SENSOR1WARNING -45
#define SENSOR2WARNING 90999
#define SENSOR3WARNING 90999
#define SENSOR4WARNING 90999
#define SENSOR5WARNING 90999
#define SENSOR6WARNING 90999

#define SENSOR1NAME "OLI"
#define SENSOR2NAME "OLI"
#define SENSOR3NAME "AIGUA"
#define SENSOR4NAME "TURBO"

int warning=-1;

float sensor1=0;
float sensor2=0;
float sensor3=0;
float sensor4=0;
float sensor1MAX=-999;
float sensor2MAX=-999;
float sensor3MAX=-999;
float sensor4MAX=-999;

unsigned long last_interrupt_time=0;
int actualScreen=1;

LiquidCrystal lcd(13,12,11,10,9,8);

void initialScreen(){
  lcd.setCursor(0,1);
  lcd.print("  BEYRO MOTORSPORT");
  lcd.setCursor(0,2);
  lcd.print("      CIVIC EK");
}

void ledCheck(int delayTime){
  for(int i=0; i <= 255; i++){
    analogWrite(LED,i);
    delay(delayTime);
  }
  for(int i=255; i >=0 ; i--){
    analogWrite(LED,i);
    delay(delayTime);
  }  
}

void ledBlink(){
  analogWrite(LED,255);
  delay(200);
  analogWrite(LED,0);
  delay(200);
}

//for VDO 323-057 150º celsius voltage divider with 220ohms
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

void setup() {
  pinMode(BUTTON1,INPUT);
  digitalWrite(BUTTON1,HIGH);
  attachInterrupt(0, button1ISR, LOW);

  pinMode(LED,OUTPUT);
  
  pinMode(SENSOR1,INPUT);
  pinMode(SENSOR2,INPUT);
  pinMode(SENSOR3,INPUT);
  pinMode(SENSOR4,INPUT);
  pinMode(SENSOR5,INPUT);
  pinMode(SENSOR6,INPUT);

  lcd.begin (20,4);
  init_big_font(&lcd); 
  initialScreen();  
  ledCheck(2);
  ledCheck(2);
  lcd.clear();
}

void printOil(int row, int temp, float pressure){
  String values="";
  values.concat(SENSOR1NAME+String(": "));

  if (temp < 0){
    if(temp > -10){
      values.concat(" ");
    }
  }
  else if(temp < 10){
    values.concat("  ");
  }
  else if(temp < 100){
    values.concat(" ");
  }  
  values.concat(temp);
  values.concat((char)223);
  values.concat("C  ");

  char stringPressure[10];
  dtostrf(pressure,1,2,stringPressure);
  values.concat(stringPressure);
  values.concat("BAR");

  lcd.setCursor(0,row);
  lcd.print(values);
}

void printTurbo(int row, float pressure){
  String values="";
  values.concat(SENSOR4NAME+String(": "));
  char stringPressure[10];
  dtostrf(pressure,1,2,stringPressure);
  values.concat(stringPressure);
  values.concat("BAR");
  lcd.setCursor(0,row);
  lcd.print(values);  
}

void printWater(int row, int temp){
  String values="";
  values.concat(SENSOR3NAME+String(": "));

  if (temp < 0){
    if(temp > -10){
      values.concat(" ");
    }
  }
  else if(temp < 10){
    values.concat("  ");
  }
  else if(temp < 100){
    values.concat(" ");
  }  
  values.concat(temp);
  values.concat((char)223);
  values.concat("C");

  lcd.setCursor(0,row);
  lcd.print(values);
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


float getSensorVoltage(int sensor){
  return (analogRead(sensor)/1024.000)*5;
}



void checkValues(){
  sensor1 = voltage2temp(getSensorVoltage(SENSOR1));
  sensor2 = voltage2pressure(getSensorVoltage(SENSOR2));
  sensor3 = voltage2temp2(getSensorVoltage(SENSOR3));
  sensor4 = getSensorVoltage(SENSOR4);
  
  //warning led   
  if (sensor1 >= SENSOR1WARNING){
    ledCheck(1);
    if (warning == -1){
      warning=1;
      lcd.clear();
    } 
  }
  else if (sensor2 >= SENSOR2WARNING){
    ledCheck(1);
    if (warning == -1){
      warning=2;
      lcd.clear();
    }        
  }
  else if (sensor3 >= SENSOR3WARNING){
    analogWrite(LED,255);
    if (warning == -1){
      warning=3;
      lcd.clear();
    }        
  }
  else if (sensor4 >= SENSOR4WARNING){
    ledCheck(1);
    if (warning == -1){
      warning=4;
      lcd.clear();
    }       
  }  
  else{
    if (warning >= 0){
      lcd.clear();
    } 
    warning=-1;
    
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

}





void loop() {

  checkValues();
  
  if(warning > 0){
    if(warning == 1){
      bigValue(String("TEMPERATURA ")+SENSOR1NAME,2,"COMPTE!!  PERILL!!",1,sensor1, "ºC");
    }
    else if(warning == 2){
      bigValue(String("PRESSIO ")+SENSOR2NAME,4,"COMPTE!!  PERILL!!",1,sensor2, "BAR");
    }
    else if(warning == 3){
      bigValue(String("TEMPERATURA ")+SENSOR3NAME,1,"COMPTE!!  PERILL!!",1,sensor3, "ºC");
    }
  }
  
  else{

    if(actualScreen == 1){
      printOil(0,sensor1,sensor2);         
      printWater(1,sensor3);
      printTurbo(2,sensor4);
    }
    else if(actualScreen == 2){
      bigValue(String("TEMPERATURA ")+SENSOR1NAME,2,"",9,sensor1, "ºC");
    }
    else if(actualScreen == 3){
      bigValue(String("PRESSIO ")+SENSOR2NAME,4,"",9,sensor2, "BAR");
    }
    else if(actualScreen == 4){
      bigValue(String("TEMPERATURA ")+SENSOR3NAME,1,"",9,sensor3, "ºC");
    }
    else if(actualScreen == 5){
      lcd.setCursor(3,0);
      lcd.print("VALORS MAXIMS");
      printOil(1,sensor1MAX,sensor2MAX); 
      printWater(2,sensor3MAX); 
    }
  
  }
  delay(100);
}


void button1ISR(){
  unsigned long interrupt_time = millis();  
  if (interrupt_time - last_interrupt_time > DEBOUNCING){
    actualScreen=actualScreen+1;
    if(actualScreen > TOTALSCREENS){
      actualScreen=1;
    }
    lcd.clear();
    warning=0; 
  } 
  last_interrupt_time = interrupt_time;  
}


