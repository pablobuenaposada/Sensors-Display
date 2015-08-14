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
    static String PEAKNAME;
    static int PEAKCOL;
    
    static int EEPROMSENSOR1WARNINGVALUE;
    static int EEPROMSENSOR2WARNINGVALUE;
    static int EEPROMSENSOR3WARNINGVALUE;
    static int EEPROMSENSOR4WARNINGVALUE;
    static int EEPROMSENSOR5WARNINGVALUE;
    static int EEPROMSENSOR6WARNINGVALUE;
    static int EEPROMSENSOR1WARNINGOPERATOR;
    static int EEPROMSENSOR2WARNINGOPERATOR;
    static int EEPROMSENSOR3WARNINGOPERATOR;
    static int EEPROMSENSOR4WARNINGOPERATOR;
    static int EEPROMSENSOR5WARNINGOPERATOR;
    static int EEPROMSENSOR6WARNINGOPERATOR;
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
