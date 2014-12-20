#include "Screen.h"
#include "Constants.h"
#include "LiquidCrystal.h"
#include "phi_big_font.h"

LiquidCrystal lcd(13,12,11,10,9,8);

Screen::Screen(){
  lcd.begin (20,4);
  init_big_font(&lcd);
}

void Screen::initialScreen(int col1, int col2, int col3, int col4, String string1, String string2, String string3, String string4){
  lcd.setCursor(col1,0);
  lcd.print(string1);
  lcd.setCursor(col2,1);
  lcd.print(string2);
  lcd.setCursor(col3,2);
  lcd.print(string3);
  lcd.setCursor(col4,3);
  lcd.print(string4);
}

void Screen::settingsSaved(){
  Constants constants;
  lcd.clear();
  lcd.setCursor(constants.SETTINGSSAVEDCOL,1);
  lcd.print(constants.SETTINGSSAVED);
  delay(1000);
  lcd.clear();   
}

void Screen::clear(){
  lcd.clear();
}

void Screen::printValue(int row, int col, boolean title, String name, float value, boolean degree, boolean decimal, String unit){
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
    values=name+String(": ");    
    char floatString[10];
    dtostrf(value,1,2,floatString);
    values.concat(floatString);    
  }
  else{
    values.concat((int)value);
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

void Screen::setCursor(int col, int row){
  lcd.setCursor(col,row);
}

void Screen::print(String string){
  lcd.print(string);
}

void Screen::bigValue(String title, int colTitle,String subTitle, int colSubtitle, int value, String units){ 
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

