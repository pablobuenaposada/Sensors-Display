#include "Sensors.h"
#include "Constants.h"

Sensors::Sensors(){  
  Constants constants;  
  pinMode(constants.SENSOR2,INPUT);
  pinMode(constants.SENSOR3,INPUT);
  pinMode(constants.SENSOR4,INPUT);
  pinMode(constants.SENSOR5,INPUT);
  pinMode(constants.SENSOR6,INPUT);
}  

//get ADC value from sensor
float Sensors::getSensorVoltage(int sensor){
  return (analogRead(sensor)/1024.000)*5;
}

//for VDO 323-057 150º celsius with voltage divider of 220ohms@1W and Vin=5.00 volts
float Sensors::getTemp057(int sensor){
  float volts=getSensorVoltage(sensor);
  return -0.05007201037*pow(volts,10) + 1.171260711*pow(volts,9) - 11.55461723*pow(volts,8) + 62.20510364*pow(volts,7) - 196.4010868*pow(volts,6) + 356.468504*pow(volts,5) - 305.3996258*pow(volts,4) - 57.02805328*pow(volts,3) + 378.5236931*pow(volts,2) - 366.4523339*volts + 243.2379721;
}

//for VDO 360-004 10 BAR pressure sender with voltage divider of 220ohms@1W and Vin=5.00 volts
float Sensors::getPress004(int sensor){
  float volts=getSensorVoltage(sensor);
  return 0.345207949*pow(volts,8) - 3.597256695*pow(volts,7) + 15.88816089*pow(volts,6) - 38.43159587*pow(volts,5) + 55.09001405*pow(volts,4) - 46.88577533*pow(volts,3) + 23.34568903*pow(volts,2) - 3.67372459*volts + 0.07053106278;
}


