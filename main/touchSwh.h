#pragma once
#include <Arduino.h>
class TouchSwh{
  public:
    TouchSwh();
    TouchSwh(int signal);
    ~TouchSwh();
    int State();
  private:
    int signal;
    
//  private:
    
};
