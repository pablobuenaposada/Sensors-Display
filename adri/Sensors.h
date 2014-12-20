#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"

class Sensors{
  public:
    Sensors();
    float getTemp057(int sensor);
    float getPress004(int sensor);
  private:
    float getSensorVoltage(int sensor);
};

#endif
