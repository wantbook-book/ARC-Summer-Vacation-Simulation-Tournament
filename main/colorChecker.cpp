#include "colorChecker.h"
ColorChecker::ColorChecker(){
  
}
ColorChecker::~ColorChecker(){
  
}
ColorChecker::ColorChecker(int int_pin, Camera camera, int Handling){
  this->int_pin = int_pin;
  this->camera = camera;
  this->Handling = Handling;
}

int ColorChecker::MeetColor(){
  if(digitalRead(this->int_pin) == HIGH){
    return this->camera.GetColor();
  }
  return 0;
}
