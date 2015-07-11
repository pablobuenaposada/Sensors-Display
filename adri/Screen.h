#ifndef Screen_h
#define Screen_h

#include "Arduino.h"

class Screen{
  public:
   Screen();
   void init();
   void backlight(boolean status);
   void initialScreen(int col1, int col2, int col3, int col4, String string1, String string2, String string3, String string4);
   void clear();
   void printValue(int row, int col, boolean title, String name, float value, boolean degree, boolean decimal, String unit);
   void setCursor(int col, int row);
   void print(String string);
   void bigValue(String title, int colTitle,String subTitle, int colSubtitle, int value, String units);
   void settingsSaved();
};

#endif
