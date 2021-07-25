#include "trackSensor.h"
TrackSensor::TrackSensor(){
  ;
}
TrackSensor::~TrackSensor(){
  ;
}
/*
TrackSensor::TrackSensor(Infrared infrareds[INFRARED_NUM]){
  for(int i=0; i<INFRARED_NUM; i++){
    this->infrareds[i] = infrareds[i];
  }
  this->state = MOVE_RIGHT;
}
*/
TrackSensor::TrackSensor(Infrared *infrareds[INFRARED_NUM]){
  for(int i=0; i<INFRARED_NUM; i++){
    this->infrareds[i] = *infrareds[i];
  }
  this->state = MOVE_RIGHT;
  this->count = 0;
  for(int i=0; i<5; i++){
    this->finish[i] = 0;
  }
  this->change = 0;
  this->f1 = 0;
}
int TrackSensor::Test(){
  if(!this->infrareds[F1].Deviate() && this->infrareds[F2].Deviate()){
    return 0;
  }else if(!this->infrareds[_B1].Deviate() && this->infrareds[_B2].Deviate()){
    return 1;
  }else if(!this->infrareds[L1].Deviate() && this->infrareds[L2].Deviate()){
    return 2;
  }else if(!this->infrareds[R1].Deviate() && this->infrareds[R2].Deviate()){
    return 3;
  }else{
    return 4;
  }
  
}
/*
int TrackSensor::DirSelect(){
  switch(this->state){
    case MOVE_RIGHT:{
      Serial.println("-----------MOVE_RIGHT------------");
      if(!this->infrareds[F1].Deviate() && !this->infrareds[F2].Deviate() && !this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        finish[0] = 1; 
        this->modiState(REACH_FL);
        Serial.println("-----------start to REACH_FL------------");
        return STAY;
        
      }else{
        return RIGHT;
      }
      
        break;
    }
    case REACH_FL:{
      Serial.println("-----------REACH_FL------------");
      if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        if(finish[0] != 1) break;
        this->count ++;
        if(this->count == 3){
          finish[1] = 1;
          this->modiState(ALONG_FL);
          Serial.println("-----------start to ALONG_FL------------");
          this->count = 0;
          return STAY;
          //其他情况
        }
      }
      if(this->infrareds[F1].Deviate() && !this->infrareds[F2].Deviate()){
        return TRIGHT;
      }else if(!this->infrareds[F1].Deviate() && this->infrareds[F2].Deviate()){
        return TLEFT;
      }else if(!this->infrareds[F1].Deviate() && !this->infrareds[F2].Deviate()){
        return FORWARD; 
      }else{
        Serial.println("no states compare IN REACH_FL");
        return STAY;
      }
      break;
    }
    case ALONG_FL:{
      Serial.println("-----------ALONG_FL------------");
      if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1) break;
        finish[2] = 1;
        Serial.println("-----------START TO ALONG_FL_BACK------------");
        this->modiState(ALONG_FL_BACK);
        return STAY;
        //其他情况
      }
      if(!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        return TRIGHT;
      }else if(!!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        return TLEFT;
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        return RIGHT; 
      }else{
        Serial.println("no states compare IN ALONG_FL");
        return STAY;
      }
     
      break;
    }
    case ALONG_FL_BACK:{
      Serial.println("-----------ALONG_FL_BACK------------");
      if(!this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1 || finish[2]!=1) break;
        finish[3] = 1;
        this->modiState(REACH_SDL);
        Serial.println("-----------START TO REACH_SDL------------");
        return STAY;
        //其他情况
      }
      if(!this->infrareds[L1].Deviate() && !!this->infrareds[L2].Deviate()){
        return TRIGHT;
      }else if(!!this->infrareds[L1].Deviate() && !this->infrareds[L2].Deviate()){
        return TLEFT;
      }else if(!!this->infrareds[L1].Deviate() && !!this->infrareds[L2].Deviate()){
        return LEFT; 
      }else{
        Serial.println("no states compare IN ALONG_FL_BACK");
        return STAY;
      }
      break;
    }
    case REACH_SDL:{
      Serial.println("-----------REACH_SDL------------");
      if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate() && !this->infrareds[L1].Deviate() && !this->infrareds[L2].Deviate()){
        this->count += 1;
        if(count == 2){
          if(finish[0]!=1 || finish[1]!=1 || finish[2]!=1 || finish[3]!=1) break;
          finish[4] = 1;
          Serial.println("-----------START TO ALONG_SDL------------");
          this->modiState(ALONG_SDL);
          return STAY;
        }
      }
      if(this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        return TRIGHT;
      }else if(!this->infrareds[_B1].Deviate() && this->infrareds[_B2].Deviate()){
        return TLEFT;
      }else if(!this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        return BACK; 
      }else{
        Serial.println("no states compare IN REACH_SDL");
        return STAY;
      }
      break;
    }
    case ALONG_SDL:{
      Serial.println("-----------ALONG_SDL------------");
      if(!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        return TRIGHT;
      }else if(!!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        return TLEFT;
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        return RIGHT; 
      }else if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1 || finish[2]!=1 || finish[3]!=1 || finish[4]!=1) break;
        finish[5] = 1;
        this->modiState(ALONG_FL_BACK);
        return STAY;
        //其他情况
      }else{
        Serial.println("no states compare IN ALONG_SDL");
        return STAY;
      }
     
      break;
    }
    default:
      Serial.println("no states compare");
      return STAY;
      
  }
}
*/
int TrackSensor::DirSelect(){
  
  switch(this->state){
    case MOVE_RIGHT:{
      if(!this->infrareds[F1].Deviate()){
        if(this->f1 != 1)
          this->f1 = 1;
      }
      if(!this->infrareds[F2].Deviate() && this->f1==1){
//      if(!this->infrareds[F1].Deviate() || !this->infrareds[F2].Deviate() /*&& !this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()*/){
        finish[0] = 1; 
        this->modiState(REACH_FL);
        return STAY;
        
      }else{
        return RIGHT;
      }
      
        break;
    }
    case REACH_FL:{
      if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        
        this->change = 0;
        
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        if(finish[0] != 1) break;
        if(this->change == 0){
          this->count++;
        }
        this->change = 1;
        if(this->count == 3){
          finish[1] = 1;
          this->modiState(ALONG_FL);
          this->count = 0;
          return STAY;
          //其他情况
        }
      }
      
      
      if(this->infrareds[F1].Deviate() && !this->infrareds[F2].Deviate()){
        return TRIGHT;
      }else if(!this->infrareds[F1].Deviate() && this->infrareds[F2].Deviate()){
        return TLEFT;
        
      }else if(!this->infrareds[F1].Deviate() && !this->infrareds[F2].Deviate()){
        return FORWARD; 
      }else{
        return STAY;
      }
      break;
    }
    case ALONG_FL:{
      if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1) break;
        finish[2] = 1;
        this->modiState(ALONG_FL_BACK);
        return STAY;
        //其他情况
      }
      if(!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        return TRIGHT;
      }else if(!!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        return TLEFT;
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        return RIGHT; 
      }else{
        return STAY;
      }
     
      break;
    }
    case ALONG_FL_BACK:{
      if(!this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1 || finish[2]!=1) break;
        finish[3] = 1;
        this->modiState(REACH_SDL);
        return STAY;
        //其他情况
      }
      if(!this->infrareds[L1].Deviate() && !!this->infrareds[L2].Deviate()){
        return TRIGHT;
      }else if(!!this->infrareds[L1].Deviate() && !this->infrareds[L2].Deviate()){
        return TLEFT;
      }else if(!!this->infrareds[L1].Deviate() && !!this->infrareds[L2].Deviate()){
        return LEFT; 
      }else{
        return STAY;
      }
      break;
    }
    case REACH_SDL:{
      if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        this->change = 0;
        
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1 || finish[2]!=1 || finish[3]!=1) break;
        if(this->change == 0){
          this->count++;
        }
        
        this->change = 1;
        if(this->count == 2){
          finish[4] = 1;
          this->modiState(ALONG_SDL);
          this->count = 0;
          return STAY;
          //其他情况
        }
      }
      
      if(this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        return TRIGHT;
      }else if(!this->infrareds[_B1].Deviate() && this->infrareds[_B2].Deviate()){
        return TLEFT;
      }else if(!this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        return BACK; 
      }else{
        return STAY;
      }
      break;
    }
    case ALONG_SDL:{
      if(!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        return TRIGHT;
      }else if(!!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        return TLEFT;
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        return RIGHT; 
      }else if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1 || finish[2]!=1 || finish[3]!=1 || finish[4]!=1) break;
        finish[5] = 1;
        this->modiState(ALONG_FL_BACK);
        return STAY;
        //其他情况
      }else{
        return STAY;
      }
     
      break;
    }
    default:
      return STAY;
      
  }
}

int TrackSensor::DirSelect_test(){
  switch(this->state){
    case MOVE_RIGHT:{
      Serial.println("-----------MOVE_RIGHT------------");
      delay(500);
      if(!this->infrareds[F1].Deviate() && !this->infrareds[F2].Deviate() /*&& !this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()*/){
        finish[0] = 1; 
        this->modiState(REACH_FL);
        Serial.println("-----------start to REACH_FL------------");
        delay(500);
        return STAY;
        
      }else{
        Serial.println("-----------RIGHT IN MOVE_RIGHT------------");
        delay(500);
        return RIGHT;
      }
      
        break;
    }
    case REACH_FL:{
      Serial.println("-----------REACH_FL------------");
      delay(500);
      if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        
        this->change = 0;
        
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        if(finish[0] != 1) break;
        if(this->change == 0){
          this->count++;
        }
        this->change = 1;
        Serial.println("-----------"+String(count)+"--IN REACH_FL----------");
        if(this->count == 3){
          finish[1] = 1;
          this->modiState(ALONG_FL);
          Serial.println("-----------start to ALONG_FL------------");
          delay(500);
          this->count = 0;
          return STAY;
          //其他情况
        }
      }
      
      
      if(this->infrareds[F1].Deviate() && !this->infrareds[F2].Deviate()){
        Serial.println("TRIGHT IN REACH_FL");
        delay(500);
        return TRIGHT;
      }else if(!this->infrareds[F1].Deviate() && this->infrareds[F2].Deviate()){
        Serial.println("TLEFT IN REACH_FL");
        delay(500);
        return TLEFT;
        
      }else if(!this->infrareds[F1].Deviate() && !this->infrareds[F2].Deviate()){
        Serial.println("FORWARD IN REACH_FL");
        delay(500);
        return FORWARD; 
      }else{
        Serial.println("no states compare IN REACH_FL");
        delay(500);
        return FORWARD;
      }
      break;
    }
    case ALONG_FL:{
      Serial.println("-----------ALONG_FL------------");
      delay(500);
      if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1) break;
        finish[2] = 1;
        Serial.println("-----------START TO ALONG_FL_BACK------------");
        delay(500);
        this->modiState(ALONG_FL_BACK);
        return STAY;
        //其他情况
      }
      if(!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        Serial.println("TRIGHT IN ALONG_FL");
        delay(500);
        return TRIGHT;
      }else if(!!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        Serial.println("TLEFT IN ALONG_FL");
        delay(500);
        return TLEFT;
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        Serial.println("RIGHT IN ALONG_FL");
        delay(500);
        return RIGHT; 
      }else{
        Serial.println("no states compare IN ALONG_FL");
        delay(500);
        return RIGHT;
      }
     
      break;
    }
    case ALONG_FL_BACK:{
      Serial.println("-----------ALONG_FL_BACK------------");
      delay(500);
      if(!this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1 || finish[2]!=1) break;
        finish[3] = 1;
        this->modiState(REACH_SDL);
        Serial.println("-----------START TO REACH_SDL------------");
        delay(500);
        return STAY;
        //其他情况
      }
      if(!this->infrareds[L1].Deviate() && !!this->infrareds[L2].Deviate()){
        Serial.println("TRIGHT IN ALONG_FL_BACK");
        delay(500);
        return TRIGHT;
      }else if(!!this->infrareds[L1].Deviate() && !this->infrareds[L2].Deviate()){
        Serial.println("TLEFT IN ALONG_FL_BACK");
        delay(500);
        return TLEFT;
      }else if(!!this->infrareds[L1].Deviate() && !!this->infrareds[L2].Deviate()){
        Serial.println("LEFT IN ALONG_FL_BACK");
        delay(500);
        return LEFT; 
      }else{
        Serial.println("no states compare IN ALONG_FL_BACK");
        delay(500);
        return LEFT;
      }
      break;
    }
    case REACH_SDL:{
      Serial.println("-----------REACH_SDL------------");
      delay(500);
      if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        Serial.println("======0000 IN REACH_SDL=======");
        this->change = 0;
        
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1 || finish[2]!=1 || finish[3]!=1) break;
        if(this->change == 0){
          this->count++;
        }
        
        Serial.println("-----------"+String(count)+"--IN REACH_SDL---------");
        this->change = 1;
        if(this->count == 2){
          finish[4] = 1;
          this->modiState(ALONG_SDL);
          Serial.println("-----------start to ALONG_SDL------------");
          delay(500);
          this->count = 0;
          return STAY;
          //其他情况
        }
      }
      
      if(this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        Serial.println("TRIGHT IN REACH_SDL");
        delay(500);
        return TRIGHT;
      }else if(!this->infrareds[_B1].Deviate() && this->infrareds[_B2].Deviate()){
        Serial.println("TLEFT IN REACH_SDL");
        delay(500);
        return TLEFT;
      }else if(!this->infrareds[_B1].Deviate() && !this->infrareds[_B2].Deviate()){
        Serial.println("BACK IN REACH_SDL");
        delay(500);
        return BACK; 
      }else{
        Serial.println("no states compare IN REACH_SDL");
        delay(500);
        return BACK;
      }
      break;
    }
    case ALONG_SDL:{
      Serial.println("-----------ALONG_SDL------------");
      delay(500);
      if(!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        Serial.println("TRIGHT IN ALONG_SDL");
        delay(500);
        return TRIGHT;
      }else if(!!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        Serial.println("TLEFT IN ALONG_SDL");
        delay(500);
        return TLEFT;
      }else if(!!this->infrareds[R1].Deviate() && !!this->infrareds[R2].Deviate()){
        Serial.println("RIGHT IN ALONG_SDL");
        delay(500);
        return RIGHT; 
      }else if(!this->infrareds[R1].Deviate() && !this->infrareds[R2].Deviate()){
        if(finish[0]!=1 || finish[1]!=1 || finish[2]!=1 || finish[3]!=1 || finish[4]!=1) break;
        finish[5] = 1;
        this->modiState(ALONG_FL_BACK);
        return STAY;
        //其他情况
      }else{
        Serial.println("no states compare IN ALONG_SDL");
        delay(500);
        return RIGHT;
      }
     
      break;
    }
    default:
      Serial.println("no states compare");
      return STAY;
      
  }
}
void TrackSensor::modiState(int next){
  this->state = next;
}
  
void TrackSensor::Show(){
  for(int i=0; i<INFRARED_NUM; i++){
    Serial.println(String(i) + " : " + String(this->infrareds[i].Deviate()));
  }
  Serial.println("----------------------------------------------------------");
  delay(3000);
}
