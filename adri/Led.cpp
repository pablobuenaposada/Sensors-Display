#include "Led.h"
#include "Constants.h"

int pin;

Led::Led(int outPin){
  pin=outPin;
  pinMode(pin,OUTPUT);
}

void Led::blink(int delayTime){
  Constants constants;
  digitalWrite(pin,HIGH);
  delay(delayTime);
  digitalWrite(pin,LOW);
}

void Led::setStatus(boolean mode){
  if(mode == true){
    digitalWrite(pin,HIGH);
  }
  else{
    digitalWrite(pin,LOW);
  }
}

void Led::fade(int delayTime){
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(pin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(delayTime);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(pin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(delayTime);                            
  } 
}
