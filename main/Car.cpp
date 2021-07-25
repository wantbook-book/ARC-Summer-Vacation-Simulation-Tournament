#include "Car.h"
Car::Car(){}
Car::~Car(){}
/*
Car::Car(int dirs[STPRS_NUM], int stps[STPRS_NUM], int ens[STPRS_NUM]){
  for(int i=0; i<STPRS_NUM; i++){
    this->steppers[i] = MyStepper(dirs[i], stps[i], ens[i]);
  }
}
Car::Car(MyStepper steppers[STPRS_NUM]){
  for(int i=0; i<STPRS_NUM; i++){
    this->steppers[i] = steppers[i];
  }
}*/
Car::Car(MyStepper *steppers[STPRS_NUM], Camera camera, SeedPlacer seedPlacer){
  this->camera = camera;
  this->MySeedPlacer = seedPlacer;
  this->seedPlacer = seedPlacer;
  for(int i=0; i<STPRS_NUM; i++){
    this->steppers[i] = *steppers[i];
  }
  this->Yellow_num  = 0;
  this->Blue_num    = 0;
}

void Car::Test2(){
  this->steppers[LSTP1].SetDir(CLKW);
  for(int i=0; i<10000; i++){
      steppers[LSTP1].Pulse(MIDvSpan);
   }
   this->steppers[LSTP1].SetDir(NCLKW);
  for(int i=0; i<10000; i++){
      steppers[LSTP1].Pulse(MIDvSpan);
   }
}
void Car::Go(int dir, int span){
//  for(int i=0; i<STPRS_NUM; i++){
//    this->steppers[i].Run(CLKW, STOP);
//  }

//  转动方向为从外向内看
  switch(dir){
    case 200:{
      this->steppers[LSTP2].SetDir(NCLKW);
      this->steppers[RSTP2].SetDir(CLKW);
      for(int i=0; i<1000; i++){
        this->steppers[LSTP2].Pulse(span);
        this->steppers[RSTP2].Pulse(span);
      }
      break;
    }
    
    case 100:{
      //L2 R2 L1 R1, 0, 2, 3, 1
      //
      this->steppers[LSTP1].SetDir(NCLKW);
      this->steppers[RSTP1].SetDir(NCLKW);
      this->steppers[LSTP2].SetDir(NCLKW);
      this->steppers[RSTP2].SetDir(NCLKW);
      for(int i=0; i<STEPS; i++){
        this->steppers[LSTP1].Pulse(span);
      }
      for(int i=0; i<STEPS; i++){
        this->steppers[RSTP1].Pulse(span);
      }
      for(int i=0; i<STEPS; i++){
        
        this->steppers[LSTP2].Pulse(span);
      }
      for(int i=0; i<STEPS; i++){
        
        this->steppers[RSTP2].Pulse(span);
      }
      break;
    }
    case FORWARD:{
      this->steppers[LSTP2].SetDir(NCLKW);
      this->steppers[RSTP2].SetDir(CLKW);
      for(int i=0; i<STEPS; i++){
        this->steppers[LSTP2].Pulse(span);
        this->steppers[RSTP2].Pulse(span);
      }
      break;
    }
    case LEFT:{
      this->steppers[LSTP1].SetDir(CLKW);
      this->steppers[RSTP1].SetDir(NCLKW);
      for(int i=0; i<STEPS; i++){
        this->steppers[LSTP1].Pulse(span);
        this->steppers[RSTP1].Pulse(span);
      }
      break;
    }
    case BACK:{
      this->steppers[LSTP2].SetDir(CLKW);
      this->steppers[RSTP2].SetDir(NCLKW);
      for(int i=0; i<STEPS; i++){
        this->steppers[LSTP2].Pulse(span);
        this->steppers[RSTP2].Pulse(span);
      }
      break;
    }
    case RIGHT:{
      this->steppers[LSTP1].SetDir(NCLKW);
      this->steppers[RSTP1].SetDir(CLKW);
      for(int i=0; i<STEPS; i++){
        this->steppers[LSTP1].Pulse(span);
        this->steppers[RSTP1].Pulse(span);
      }
      break;
    }
    case TRIGHT:{
      this->steppers[LSTP1].SetDir(NCLKW);
      this->steppers[RSTP1].SetDir(NCLKW);
      this->steppers[LSTP2].SetDir(NCLKW);
      this->steppers[RSTP2].SetDir(NCLKW);
      for(int i=0; i<T_STEPS; i++){
        this->steppers[LSTP1].Pulse(span);
        this->steppers[RSTP1].Pulse(span);
        this->steppers[LSTP2].Pulse(span);
        this->steppers[RSTP2].Pulse(span);
      }
      break;
    }
    case TLEFT:{
      this->steppers[LSTP1].SetDir(CLKW);
      this->steppers[RSTP1].SetDir(CLKW);
      this->steppers[LSTP2].SetDir(CLKW);
      this->steppers[RSTP2].SetDir(CLKW);
      for(int i=0; i<T_STEPS; i++){
        this->steppers[LSTP1].Pulse(span);
        this->steppers[RSTP1].Pulse(span);
        this->steppers[LSTP2].Pulse(span);
        this->steppers[RSTP2].Pulse(span);
      }
      break;
    }
  }
} 
void Car::Stop(){
  for(int i=0; i<STPRS_NUM; i++){
    this->steppers[i].Stop();
  }
  /*
  this->seedPlacer.PlaceSeed();
  delay(1000);
  
  this->seedPlacer.PlaceNoSeed();
  delay(1000);
  */
}
void Car::Test(int id){
  if(id == 0){ //0不偏， 1偏
    this->steppers[LSTP1].SetDir(CLKW);//R2
    for(int i=0; i<STEPS; i++){
      steppers[LSTP1].Pulse(MIDvSpan);
    }
    this->steppers[LSTP1].SetDir(NCLKW);
    for(int i=0; i<STEPS; i++){
      steppers[LSTP1].Pulse(MIDvSpan);
    }
  }else if(id == 1){//4不偏， 5偏
    this->steppers[RSTP1].SetDir(CLKW);//4P 5BP, L1 方向不变 且只一次
    for(int i=0; i<STEPS; i++){
      steppers[RSTP1].Pulse(MIDvSpan);
    }
    this->steppers[RSTP1].SetDir(NCLKW);
    for(int i=0; i<STEPS; i++){
      steppers[RSTP1].Pulse(MIDvSpan);
    }
  }else if(id == 2){//6不偏， 7偏
    this->steppers[LSTP2].SetDir(CLKW);
    for(int i=0; i<STEPS; i++){
      steppers[LSTP2].Pulse(MIDvSpan);
    }
    this->steppers[LSTP2].SetDir(NCLKW);
    for(int i=0; i<STEPS; i++){
      steppers[LSTP2].Pulse(MIDvSpan);
    }
  }else if(id == 3){//2不偏， 3偏
    this->steppers[RSTP2].SetDir(CLKW);//R1
    for(int i=0; i<STEPS; i++){
      steppers[RSTP2].Pulse(MIDvSpan);
    }
    this->steppers[RSTP2].SetDir(NCLKW);
    for(int i=0; i<STEPS; i++){
      steppers[RSTP2].Pulse(MIDvSpan);
    }
  }else if(id == 4){//其他情况停
    for(int i=0; i<STPRS_NUM; i++){
      steppers[i].Stop();
    }
  }
}
void Car::Handle(int color){
  this->count++;
//  Serial.println(String(this->count) + " interrupt");
  switch(color){
    case YELLOW:{
//      Serial.println("find yellow");
      this->handle_yellow();
      break;
    }
    case BLUE:{
//      Serial.println("find blue");
     this->handle_blue();
     break;
    }
    default:{
      this->handle_green();
      break;
    }
  }
}


void Car::handle_yellow(){
  this->Yellow_num++;
//  Serial.print("yellow: ");
//  Serial.println(this->Yellow_num);
  this->seedPlacer.PlaceNoSeed();
}
void Car::handle_blue(){
  this->Blue_num++;
//  Serial.print("blue: ");
//  Serial.println(this->Blue_num);
  this->seedPlacer.PlaceSeed();
}
void Car::handle_green(){
  Serial.println("wocao");
  delay(3000);
}
