#include "infrared.h"
Infrared::Infrared(){
  ;
}
Infrared::~Infrared(){
  ;
}
Infrared::Infrared(int sigFoot){
  this->sigFoot = sigFoot;
}

int Infrared::Deviate(){
  return digitalRead(this->sigFoot)==1 ? 1:0;
}
