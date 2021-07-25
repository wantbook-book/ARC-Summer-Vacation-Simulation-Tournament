#pragma once
#include <Arduino.h>
class Infrared{
  public:
    Infrared();
    ~Infrared();
    Infrared(int sigFoot);
    int Deviate();        //红外是否出白线了
  private:
    int sigFoot;
};
