#include "myStepper.h"
MyStepper::MyStepper(){;}
MyStepper::MyStepper(int dir, int stp, int en){
  this->dir = dir;
  this->stp = stp;
  this->en  = en; 
}
MyStepper::~MyStepper(){;}

//void MyStepper::Run(/*int id,*/ int dir, int speed){
/*  digitalWrite(this->en, HIGH);
  
  if(dir == CLKW){
    digitalWrite(this->dir, HIGH);  
  }else{
    digitalWrite(this->dir, LOW);
  }
  
  switch(speed){
    case _LOW:{
         pulse(LOWvSpan);
         break;
    }
    case MID:{
        pulse(MIDvSpan);
        break;
    }
    case _HIGH:{
        pulse(HIGHvSpan);
        break;
    }
    case STOP:{
        pulse(STOPvSpan);
        break;
    }
//    case ROTATE:{
//        for(int i=0; i<ROTATE_STEPS; i++){
//          digitalWrite(this->stp, HIGH);
//          delayMicroseconds(MIDvSpan);
//          digitalWrite(this->stp, LOW);
//          delayMicroseconds(MIDvSpan);
//        }
//    }
  }
  
}
*/
void MyStepper::Pulse(int span){
    digitalWrite(this->stp, HIGH);
    delayMicroseconds(span);
    digitalWrite(this->stp, LOW);
    delayMicroseconds(span);
}
void MyStepper::SetDir(int dirVoltage){
  
  digitalWrite(this->dir, dirVoltage);
  
}
void MyStepper::Stop(){
  digitalWrite(this->stp, LOW);
}
