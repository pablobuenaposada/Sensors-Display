#include "Sensors.h"
#include "Constants.h"

#define SELPIN 10 //Selection Pin 
#define DATAOUT 11 //MOSI 
#define DATAIN  12 //MISO 
#define SPICLOCK  13 //Clock 

Sensors::Sensors(){
  Constants constants;
  pinMode(SELPIN, OUTPUT); 
  pinMode(DATAOUT, OUTPUT); 
  pinMode(DATAIN, INPUT); 
  pinMode(SPICLOCK, OUTPUT); 
  //disable device to start with 
  digitalWrite(SELPIN,HIGH); 
  digitalWrite(DATAOUT,LOW); 
  digitalWrite(SPICLOCK,LOW);  
}  

int read_mcp(int channel){
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits|=((channel-1)<<3);

  digitalWrite(SELPIN,LOW); //Select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    digitalWrite(DATAOUT,commandbits&1<<i);
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);    
  }

  digitalWrite(SPICLOCK,HIGH);    //ignores 2 null bits
  digitalWrite(SPICLOCK,LOW);
  digitalWrite(SPICLOCK,HIGH);  
  digitalWrite(SPICLOCK,LOW);

  //read bits from adc
  for (int i=11; i>=0; i--){
    adcvalue+=digitalRead(DATAIN)<<i;
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);
  }
  digitalWrite(SELPIN, HIGH); //turn off device
  return adcvalue;
}

//get ADC value from sensor
float Sensors::getSensorVoltage(int sensor){
  return (analogRead(sensor)/1024.000)*5;
}

//for VDO 323-057 150º celsius with voltage divider of 56 ohms@1W and Vin=5.00 volts
float Sensors::getTemp323057(int sensor){
  
  float volts = (read_mcp(sensor)/4095.0)*5.0;
  float v = volts;

  float rv = 342.0406525;
  rv += 53.30656433 * v; // pow(volts, 1)
  v*= volts;
  rv += -1782.286594 * v;  // 2
  v*= volts;
  rv += +4061.676731 * v;
  v*= volts;
  rv += -4566.827221 * v;
  v*= volts;
  rv += 3037.582741 * v;
  v*= volts;
  rv += -1268.136896 * v;
  v*= volts;
  rv += +335.8665566 * v;
  v*= volts;
  rv += -54.79044923 * v;
  v*= volts;
  rv += +5.021263808 * v;
  v*= volts;
  rv += -0.1977905036 * v;  // 10
  
  return rv;
}

//for VDO 323-059 150º celsius with voltage divider of 56 ohms@1W and Vin=5.00 volts
float Sensors::getTemp323059(int sensor){
  
  float volts = (read_mcp(sensor)/4095.0)*5.0;
  float v = volts ;

  float rv = 342.0406525;
  rv += 53.30656433 * v; // pow(volts, 1)
  v*= volts;
  rv += -1782.286594 * v;  // 2
  v*= volts;
  rv += +4061.676731 * v;
  v*= volts;
  rv += -4566.827221 * v;
  v*= volts;
  rv += 3037.582741 * v;
  v*= volts;
  rv += -1268.136896 * v;
  v*= volts;
  rv += +335.8665566 * v;
  v*= volts;
  rv += -54.79044923 * v;
  v*= volts;
  rv += +5.021263808 * v;
  v*= volts;
  rv += -0.1977905036 * v;  // 10
  
  return rv;
}

//for VDO 360-004 10 bar with voltage divider of 56 ohms@1W and Vin=5.00 volts
float Sensors::getPress360004(int sensor){
 
  float volts = (read_mcp(sensor)/4095.0)*5.0;
  float v = volts;

  float rv = -4.552292049;
  rv += +18.74930835 * v; // pow(volts, 1)
  v*= volts;
  rv += -32.73438168 * v;  // 2
  v*= volts;
  rv += +31.04020166 * v;  // 3
  v*= volts;
  rv += -16.67003584 * v;  // 4
  v*= volts;
  rv += +5.133446336 * v;  // 5
  v*= volts;
  rv += -0.8432134613 * v; // 6
  v*= volts;
  rv += +0.05764606735 * v;// 7
 
  return rv;
}




