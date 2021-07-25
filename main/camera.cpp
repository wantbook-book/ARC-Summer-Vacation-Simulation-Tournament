#include "camera.h"
Camera::Camera(){
  
}
Camera::~Camera(){
  
}
/*
Camera::Camera(int found, int yellow, int blue, int Handling){
  this->found = found;
  this->yellow = yellow;
  this->blue = blue;
  this->Handling = Handling;
}*/
Camera::Camera(int yellow, int blue){
  this->yellow = yellow;
  this->blue = blue;
  
}

int Camera::GetColor(){
  /*
  while(1){
    int y = digitalRead(this->yellow);
    
    int b = digitalRead(this->blue);
    Serial.println("yellow: "+String(y));
    Serial.println("blue: "+String(b));
    break;
  }
  */
  int y = digitalRead(this->yellow);
  int b = digitalRead(this->blue);
  Serial.print("blue:");
  Serial.println(b);
  delay(1000);
  Serial.print("yellow:");
  Serial.println(y);
  delay(1000);
  if(b == 1 && y != 1) return BLUE;
  if(y == 1 && b != 1) return YELLOW;
  return 0;
}
