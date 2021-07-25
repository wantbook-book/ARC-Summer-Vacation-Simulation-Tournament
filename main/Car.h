#pragma once
#include "myStepper.h"
#include "common.h"
#include "Camera.h"
#include "TrackSensor.h"
#include "myarduino.h"
#include "seedPlacer.h"
class Car{
  public:
    void Go(int dir, int span); //方向仍是FORWARD， _speed 取MIDvSpan 
    void Stop();                  //停止
    Car();
//    Car(int dirs[STPRS_NUM], int stps[STPRS_NUM], int ens[STPRS_NUM]);
//    Car(MyStepper steppers[STPRS_NUM]);
    Car(MyStepper *steppers[STPRS_NUM], Camera camera, SeedPlacer seedPlacer);
    ~Car();
    void Handle(int color);              //处理颜色, 处理过程自动设置handling 1或0
    void Test(int id);
    void Test2();
    int Yellow_num;
    int Blue_num;
    SeedPlacer MySeedPlacer;
  private:
    MyStepper steppers[STPRS_NUM];
    Camera camera;
    SeedPlacer seedPlacer;
    void handle_yellow();
    void handle_blue();
    void handle_green();
    
    int count;
    
};
