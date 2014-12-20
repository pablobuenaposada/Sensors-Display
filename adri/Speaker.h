#ifndef Speaker_h
#define Speaker_h

#include "Arduino.h"

class Speaker{
  public:
    Speaker();
    void speakerTone(int duration);
    void setStatus(boolean mode);
    boolean getStatus();
};

#endif
