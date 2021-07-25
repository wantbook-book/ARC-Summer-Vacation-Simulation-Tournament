#include "seedPlacer.h"
SeedPlacer::SeedPlacer(){
  
}
SeedPlacer::~SeedPlacer(){
  
}
SeedPlacer::SeedPlacer(Servo servo, MyStepper stepper){
  this->servo = servo;
  this->stepper = stepper;
  this->count=0;
}

void SeedPlacer::PlaceSeed(){
  
  for(int i=START_ANGLE; i<=END_ANGLE; i++){
    this->servo.write(i);
    delay(15); 
  }
//  delay(1000);
  loadSeed();
  delay(2000);
  for(int i=END_ANGLE; i>=START_ANGLE; i--){
    this->servo.write(i);
    delay(15); 
  }
}
void SeedPlacer::PlaceNoSeed(){
  for(int i=START_ANGLE; i<=END_ANGLE; i++){
    this->servo.write(i);
    delay(15); 
  }
  delay(500);
  for(int i=END_ANGLE; i>=START_ANGLE; i--){
    this->servo.write(i);
    delay(15); 
  }
}

void SeedPlacer::loadSeed(){
  if(this->count == 0){
    this->stepper.SetDir(CLKW);
    for(int i=0; i<STEPS_90*2; i++){
      this->stepper.Pulse(MIDvSpan);
      delay(1);
    }
    this->count =1;
  }else{
    this->stepper.SetDir(CLKW);
    for(int i=0; i<STEPS_90; i++){
      this->stepper.Pulse(MIDvSpan);
      delay(1);
    }
  }
  
}
