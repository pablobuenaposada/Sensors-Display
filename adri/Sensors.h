#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"

class Sensors{
  public:
    Sensors();
    float getTemp323057(int sensor);
    float getTemp323059(int sensor);
    float getPress360004(int sensor);
  private:
    float getSensorVoltage(int sensor);
};

#endif
