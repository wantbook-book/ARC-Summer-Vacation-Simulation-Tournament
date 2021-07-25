/*
  ----- |
   |    |
   |    |
   |  -----   
*/
#define BLUE_SIG_OUT  A0  //6
#define YELLOW_SIG_OUT A1 //4
#define INTERRUPT_PIN 21  //P4
#define YELLOW_PIN    20  //P3
//#define BLUE_PIN    23  //P2
#define BLUE_PIN      27  //P0
#define HANDLING_PIN  25  //P1
#define SERVO_PIN 2
#define SEED_DIR  13
#define SEED_STP  15
#define SEED_EN   17

#include <Servo.h>
#include "Car.h"
#include "myStepper.h"
#include "infrared.h"
#include "trackSensor.h"
#include "common.h"
#include <Servo.h>
#include <LiquidCrystal.h>
#include "seedPlacer.h"
#include "colorChecker.h"
//#include 

/*---------函数声明-----------------------------*/
void color_found();
void setContents(LiquidCrystal lcd, int blue, int yellow, int green);
void show(LiquidCrystal lcd, int _delay);
/*---------函数声明-----------------------------*/

/*---------引脚-----------------------------*/
const int dir[STPRS_NUM] = {46, 4, 16, 49};
const int stp[STPRS_NUM] = {44, 5, 19, 51};
const int en[STPRS_NUM]  = {42, 7, 18, 53};
const int fraSig[INFRARED_NUM] = {24, 26, 0, 0, 48, 50, 0, 0};
//26, 24, A6, A10, 50, 48, A12, A8
/*---------引脚-----------------------------*/
//4,5,7,3, 1, 0, 6, 2

MyStepper *steppers[STPRS_NUM];
Car car;
Camera camera;
Servo myservo;
Infrared *infrareds[INFRARED_NUM];
TrackSensor trackSensor;
SeedPlacer seedPlacer;
MyStepper seed_stepper;
ColorChecker colorChecker;
int dirSelect;
int color;
int flag = 0;
int count =0;
int count_f = 0;
void setup(){
/*--------------LED----------------------*/
    pinMode(BLUE_SIG_OUT, OUTPUT);
    pinMode(YELLOW_SIG_OUT, OUTPUT);
    digitalWrite(BLUE_SIG_OUT, LOW);
    digitalWrite(YELLOW_SIG_OUT, LOW);   
/*--------------LED----------------------*/
/*---------种子投放者-----------------------------*/
    pinMode(SEED_DIR, OUTPUT);
    pinMode(SEED_STP, OUTPUT);
    pinMode(SEED_EN, OUTPUT);
    digitalWrite(SEED_EN, HIGH);
    
    myservo.attach(SERVO_PIN);
    seed_stepper = MyStepper(SEED_DIR, SEED_STP, SEED_EN);
    seedPlacer = SeedPlacer(myservo, seed_stepper);
/*---------种子投放者-----------------------------*/
    
/*---------轮子电机-----------------------------*/
    for(int i=0; i<STPRS_NUM; i++){
      pinMode(dir[i], OUTPUT);
      pinMode(stp[i], OUTPUT);
      pinMode(en[i], OUTPUT);
    }
    for(int i=0; i<STPRS_NUM; i++){
      digitalWrite(en[i], HIGH);
    }
    for(int i=0; i<STPRS_NUM; i++){
      steppers[i] = new MyStepper(dir[i], stp[i], en[i]);
    }
/*---------轮子电机-----------------------------*/

/*---------红外-----------------------------*/
    pinMode(A8, INPUT);  //0
    pinMode(A10, INPUT);   //1
    pinMode(A12, INPUT);
    pinMode(A6, INPUT);
    for(int i=0; i<2; i++){
      pinMode(fraSig[i], INPUT);
    }
    for(int i=4; i<6; i++){
      pinMode(fraSig[i], INPUT);
    }
    infrareds[2] = new Infrared(A6);
    infrareds[3] = new Infrared(A10);
    infrareds[6] = new Infrared(A12);
    infrareds[7] = new Infrared(A8);
    for(int i=0; i<2; i++){
      infrareds[i] = new Infrared(fraSig[i]);
    }
    for(int i=4; i<6; i++){
      infrareds[i] = new Infrared(fraSig[i]);
    }

/*---------红外-----------------------------*/


/*---------camera-----------------------------*/
    pinMode(HANDLING_PIN, OUTPUT);
    digitalWrite(HANDLING_PIN, LOW);
    pinMode(BLUE_PIN, INPUT);
    pinMode(YELLOW_PIN, INPUT);
//    camera = Camera(YELLOW_PIN, BLUE_PIN, HANDLING_PIN);
  camera = Camera(YELLOW_PIN, BLUE_PIN);
  /*---------颜色检测器-----------------------------*/    
    colorChecker = ColorChecker(INTERRUPT_PIN, camera, HANDLING_PIN);
    trackSensor = TrackSensor(infrareds);
/*---------camera-----------------------------*/

//可用来注册中断的口， 2, 3, 18, 19, 20, 21
//    pinMode(INTERRUPT_PIN, INPUT);
//    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), color_found, RISING); //上升沿触发

/*---------car-----------------------------*/
    car = Car(steppers, camera, seedPlacer);
/*---------car-----------------------------*/
    Serial.begin(9600);
    
  /*---------delete-----------------------------*/
    for(int i=0; i<STPRS_NUM; i++){
      delete steppers[i];
    }
    for(int i=0; i<INFRARED_NUM; i++){
      delete infrareds[i];
    }
/*---------delete-----------------------------*/


}
void loop(){
//  seedPlacer.PlaceSeed();

// while(0)
// {
////  digitalWrite(HANDLING_PIN, LOW);
//  while(1){
//    trackSensor.Show();
//  }
//  while(1){
//  Serial.print(digitalRead(INTERRUPT_PIN));
//  Serial.print(";");
//  Serial.print(digitalRead(HANDLING_PIN));
//  Serial.print(";");
//  Serial.print(digitalRead(YELLOW_PIN));
//  Serial.print(";");
//  Serial.print(digitalRead(BLUE_PIN));
//  Serial.print("\n");
//  delay(2000);
//  }
//    color = colorChecker.MeetColor();
//  
////    Serial.println(String(color));
//  if(color != 0){
//    car.Stop();
//    Serial.print("color:");
//    Serial.print(color);
//    Serial.print("\n");
//    digitalWrite(colorChecker.Handling, HIGH);
//    car.Handle(color);
//    digitalWrite(colorChecker.Handling, LOW);
//    
//  }
//  
// }

  


    color = colorChecker.MeetColor();
    if(color != NOCOLOR){
      car.Stop();
      digitalWrite(colorChecker.Handling, HIGH);
      if(color == YELLOW){
        digitalWrite(YELLOW_SIG_OUT, HIGH);
        digitalWrite(BLUE_SIG_OUT, LOW);
        delay(1000);
        digitalWrite(YELLOW_SIG_OUT, LOW);
      }else if(color == BLUE){
        digitalWrite(BLUE_SIG_OUT, HIGH);
        digitalWrite(YELLOW_SIG_OUT, LOW);
        delay(1000);
        digitalWrite(BLUE_SIG_OUT, LOW);
      }
      
      car.Handle(color);
      digitalWrite(colorChecker.Handling, LOW);
      
    }
    dirSelect = trackSensor.DirSelect_test();
    if(dirSelect == TLEFT || dirSelect == TRIGHT){
      car.Go(dirSelect, LOWvSpan);
    }else if(dirSelect == STAY){
      car.Stop();
    }else{
      car.Go(dirSelect, MIDvSpan);
    }
  
}





void color_found(){
//  car.Stop();
//  delay(6000);
//  car.Handle();
//  delay(6000);
  /*
  for(int i=0; i<3; i++){
    dirSelect = trackSensor.DirSelect();
    if(dirSelect == TLEFT || dirSelect == TRIGHT){
      car.Go(dirSelect, LOWvSpan);
    }else if(dirSelect == STAY){
      car.Stop();
    }else{
      car.Go(dirSelect, MIDvSpan);
    }
  }*/
  count ++;
  Serial.println(String(count) + "此");
 
}


void setContents(LiquidCrystal lcd, int blue, int yellow, int green){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BLUE ");
  lcd.print("YELLOW ");
  lcd.print("GREEN");
  lcd.setCursor(1, 0);
  lcd.print(String(blue));
  lcd.setCursor(1, 5);
  lcd.print(String(yellow));
  lcd.setCursor(1, 12);
  lcd.print(String(green));
}
void show(LiquidCrystal lcd, int _delay){
  lcd.noDisplay();
  delay(_delay);
  lcd.display();
  delay(_delay);
}
