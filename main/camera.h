#pragma once
#include "common.h"
#include "myarduino.h"
//找个颜色， 提供个handling信号脚
class Camera{
  public:
    Camera();
    ~Camera();
//    Camera(int found, int yellow, int blue, int Hanling);
    Camera(int yellow, int blue);
//    int Found();
    int GetColor();       //返回颜色
//    void Done();
  private:
    int found;
    int yellow;
    int blue;
};
