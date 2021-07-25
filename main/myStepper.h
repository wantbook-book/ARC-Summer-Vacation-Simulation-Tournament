#pragma once
#include "common.h"
#include "myarduino.h"
class MyStepper{
  public:
    MyStepper();
    MyStepper(int dir, int stp, int en);
    ~MyStepper();
//    void Run(/*int id,*/ int dir, int speed);
    void Stop();          //不给脉冲
    void Pulse(int span); //给限定间隔的脉冲
    void SetDir(int dirVoltage); //设置方向
  private:
    int dir;
    int stp;
    int en;
//    void pulse(int span);
};
