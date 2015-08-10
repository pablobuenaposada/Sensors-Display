#ifndef Led_h
#define Led_h

#include "Arduino.h"

class Led{
  public:
    Led(int outPin);
    void blink(int delayTime);
    void setStatus(boolean mode);
    void fade(int delayTime);
  private:
    int pin;
};

#endif
