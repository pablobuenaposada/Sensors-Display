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

//for VDO 323-057 150º celsius with voltage divider of 56ohms 1W
float Sensors::getTemp057(int sensor){
  float volts=getSensorVoltage(sensor);  
  return (-9.805174198*pow(10,-1)*pow(volts,9)+23.4368155*pow(volts,8)-240.7430517*pow(volts,7)+1390.11628*pow(volts,6)-4955.008229*pow(volts,5)+11266.31187*pow(volts,4)-16289.93484*pow(volts,3)+14423.41426*pow(volts,2)-7152.975474*volts+1697.497838);
}

//for VDO 360-004 10 BAR pressure sender with voltage divider of 56ohms 1W
float Sensors::getPress004(int sensor){
  float volts=getSensorVoltage(sensor);
  return 7.671035919*pow(10,-2)*pow(volts,7)-1.077184901*pow(volts,6)+6.295494139*pow(volts,5)-19.62567902*pow(volts,4)+35.08161116*pow(volts,3)-35.51613665*pow(volts,2)+19.52857924*volts-4.551671147;
}


