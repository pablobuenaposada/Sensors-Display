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

//for VDO 323-057 150º celsius with voltage divider of 56ohms@1W and Vin=5.00 volts
float Sensors::getTemp057(int sensor){
  float volts=getSensorVoltage(sensor);
  return -1.977905036*pow(10,-1)*pow(volts,10)+5.021263808*pow(volts,9)-54.79044923*pow(volts,8)+335.8665566*pow(volts,7)-1268.136896*pow(volts,6)+3037.582741*pow(volts,5)-4566.827221*pow(volts,4)+4061.676731*pow(volts,3)-1782.286594*pow(volts,2)+53.30656433*volts+342.0406525;
}

//for VDO 360-004 10 BAR pressure sender with voltage divider of 56ohms@1W and Vin=5.00 volts
float Sensors::getPress004(int sensor){
  float volts=getSensorVoltage(sensor);
  return 5.764606735*pow(10,-2)*pow(volts,7)-8.432134613*pow(10,-1)*pow(volts,6)+5.133446336*pow(volts,5)-16.67003584*pow(volts,4)+31.04020166*pow(volts,3)-32.73438168*pow(volts,2)+18.74930835*volts-4.552292049;
}


