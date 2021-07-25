#include "touchSwh.h"
TouchSwh::TouchSwh(int signal){
  this->signal = signal;
}
int TouchSwh::State(){
  return digitalRead(this->signal);
}
