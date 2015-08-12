#ifndef Variables_h
#define Variables_h

#include "Arduino.h"

class Variables{
  public:
   Variables();
   static int actualScreen;
   static unsigned long last_interrupt_time;
   static int feature;
   static boolean featureFlag;
   static int alarmfeature;
   static boolean alarmFlag;
   static int warningScreen;
   static int SENSOR1WARNINGMAX;
   static int SENSOR2WARNINGMAX;
   static int SENSOR3WARNINGMAX;
   static int SENSOR4WARNINGMAX;
   static int SENSOR5WARNINGMAX;
   static int SENSOR6WARNINGMAX;
   static int SENSOR1WARNINGMIN;
   static int SENSOR2WARNINGMIN;
   static int SENSOR3WARNINGMIN;
   static int SENSOR4WARNINGMIN;
   static int SENSOR5WARNINGMIN;
   static int SENSOR6WARNINGMIN;
   static float sensor1;
   static float sensor2;
   static float sensor3;
   static float sensor4;
   static float sensor5;
   static float sensor6;
   static float sensor1MAX;
   static float sensor2MAX;
   static float sensor3MAX;
   static float sensor4MAX;
   static float sensor5MAX;
   static float sensor6MAX;
   
   static boolean clearLCD;
};

#endif
