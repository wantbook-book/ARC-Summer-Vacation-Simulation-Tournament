#pragma once

//电机转动方向
#define NCLKW    1
#define CLKW     0

//前进速度选择，控制脉冲频率
#define ROTATE   200
#define ROTATE_STEPS 1000 //使他转60度

//#define _LOW      0
#define LOWvSpan  350 
//#define MID       1
//#define MIDvSpan  300
#define MIDvSpan  200
//#define _HIGH     2
#define HIGHvSpan 250
//#define STOP      3
#define STOPvSpan 60000

//电机标号
#define LSTP1     0
#define RSTP1     2
#define LSTP2     3
#define RSTP2     1

//电机数量
#define STPRS_NUM  4

//红外数量
#define INFRARED_NUM  8

//应该转向
//前进方向选择
#define TRIGHT    5
#define TLEFT     6
#define FORWARD   0
#define RIGHT     1
#define BACK      2
#define LEFT      3
#define STAY      4
#define HANDLE_COLOR 7
//默认一次判断前进的步数
#define STEPS     300
#define T_STEPS   150
//#define STEPS     10
//#define T_STEPS   10

//麦克纳姆轮车, 电机最大速度
//#define MAX_SPEED   2000
//#define MICRO_STEP  1
//#define MID_SPEED   1500

//颜色
#define NOCOLOR 0
#define YELLOW  1
#define BLUE    2

//seedPlacer
#define START_ANGLE 60
#define END_ANGLE   140
#define STEPS_90    400
