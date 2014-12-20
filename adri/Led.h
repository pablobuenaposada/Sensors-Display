#ifndef Led_h
#define Led_h

#include "Arduino.h"

class Led{
  public:
    Led();
    void ledBlink(int delayTime);
};

#endif
