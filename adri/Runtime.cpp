#include "Runtime.h"

Runtime::Runtime(){ 
}

String Runtime::getTime(){
  unsigned long t = millis()/1000;
  static char str[9];
  int h = t / 3600;
  t = t % 3600;
  int m = t / 60;
  int s = t % 60;
  sprintf(str, "%02d:%02d:%02d", h, m, s);
  return str;
}
