#ifndef Constants_h
#define Constants_h

#include "Arduino.h"

class Constants{
  public:
    static int LED;
    static int RELAY1;
    static int LEDDURATION;
    static int SPEAKERDURATION;
    static int EEPROMSPEAKER;
    static String SETTINGSSAVED;
    static int SETTINGSSAVEDCOL;
    static String SETTINGS;
    static int SETTINGSCOL;
    static int ALARMPRESSINGTIME;
    static String ALARMNAME;
    static int ALARMNAMECOL;
    static int DEBOUNCING;
    static int BUTTON1;
    static int BUTTON2;
    static int TOTALSCREENS;    
    static int INITCOL1;
    static String INITSTRING1;
    static int INITCOL2;
    static String INITSTRING2;
    static int INITCOL3;
    static String INITSTRING3;
    static int INITCOL4;
    static String INITSTRING4;
    
    static int REFRESHRATE;
    
    static int SENSORMCP1;  //VDO 150 grados
    static int SENSORMCP2; //presion 
    static int SENSORMCP3; //VDO 120 grados
    static int SENSORMCP4;
    static int SENSORMCP5;
    static int SENSORMCP6;
    static int SENSORMCP7;
    static int SENSORMCP8;
    
    static String WARNINGSTRING;
    static int WARNINGCOL;
    static String PEAKSTRING;
    static int PEAKCOL;
    
    static int EEPROMSENSOR1WARNINGMAX;
    static int EEPROMSENSOR2WARNINGMAX;
    static int EEPROMSENSOR3WARNINGMAX;
    static int EEPROMSENSOR4WARNINGMAX;
    static int EEPROMSENSOR5WARNINGMAX;
    static int EEPROMSENSOR6WARNINGMAX;
    static int EEPROMSENSOR1WARNINGMIN;
    static int EEPROMSENSOR2WARNINGMIN;
    static int EEPROMSENSOR3WARNINGMIN;
    static int EEPROMSENSOR4WARNINGMIN;
    static int EEPROMSENSOR5WARNINGMIN;
    static int EEPROMSENSOR6WARNINGMIN;
    static String SENSOR1NAME;
    static String SENSOR1UNITS;
    static String SENSOR1BIG;
    static int SENSOR1BIGCOL;
    static String SENSOR2NAME;
    static String SENSOR2UNITS;
    static String SENSOR2BIG;
    static int SENSOR2BIGCOL;
    static String SENSOR3NAME;
    static String SENSOR3UNITS;
    static String SENSOR3BIG;
    static int SENSOR3BIGCOL;
    static String SENSOR4NAME;
    static String SENSOR4UNITS;
    static String SENSOR5NAME;
    static String SENSOR5UNITS;
    static String SENSOR6NAME;
    static String SENSOR6UNITS; 
     
    static String TIMENAME; 

};

#endif
