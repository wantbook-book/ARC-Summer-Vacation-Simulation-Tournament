#pragma once
#include "common.h"
#include "camera.h"
class ColorChecker{
  public:
    ColorChecker();
    ~ColorChecker();
    ColorChecker(int int_pin, Camera camera, int Handling);
    int Handling;
    int MeetColor();
  private:
    int int_pin;
    Camera camera;
};
