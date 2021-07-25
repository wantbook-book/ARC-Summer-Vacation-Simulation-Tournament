#pragma once
#include "common.h"
#include "infrared.h"
#include "myarduino.h"
//红外传感器标号
#define F1  0
#define F2  1
#define R1  2
#define R2  3
#define _B1 4
#define _B2 5
#define L1  6
#define L2  7
//4,5,7,3, 1, 0, 6, 2
//状态
#define MOVE_RIGHT    0
#define REACH_FL      1
#define ALONG_FL      2
#define ALONG_FL_BACK 3
#define REACH_SDL     4
#define ALONG_SDL     5

class TrackSensor{
  public:
    TrackSensor();
    ~TrackSensor();
    TrackSensor(Infrared *infrareds[INFRARED_NUM]); //给入四个红外传感器
    int DirSelect();                                //返回各个状态小车该前进的方向或转弯方向,. 检测是否有色块
    void Show();                                    //显示各个传感器的信号
    int Test();
    int DirSelect_test();                            //有打印状态
  private:
    Infrared infrareds[INFRARED_NUM];
    int f1;
    int state;
    int finish[5];
    void modiState(int next);
    int count;
    int change;
};
