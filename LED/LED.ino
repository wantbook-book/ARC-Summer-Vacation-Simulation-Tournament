
#define BLUE_SIG    6
#define YELLOW_SIG  4
#define LED_NUM     7
//#define BLUE_NUM    6
//#define YELLOW_NUM  4
#define BLUE_NUM    7
#define YELLOW_NUM  7
int BlueCount;
int BlueLastState;
int YellowCount;
int YellowLastState;
//const int BlueLED[BLUE_NUM] = {7, 13, 3, 9, /*15,*/ 5, 11};
//const int YellowLED[YELLOW_NUM] = {21, /*27,*/ 17, 23,/* 29, 19,*/ 25};
//const int BlueLED[BLUE_NUM] = {7, 13, 3, 9, 15, 5, 11};
//const int YellowLED[YELLOW_NUM] = {21, 27, 17, 23, 29, 19, 25};
const int BlueLED[BLUE_NUM] = {3, 5, 7, 9, 11, 13, 15};
const int YellowLED[YELLOW_NUM] = {29, 27, 25, 23, 21, 19, 17};
void ChcekLight();
void ShowBlueLED();
void ShowYellowLED();
void setup() {
  BlueCount = 0;
  BlueLastState = 0;
  YellowCount = 0;
  YellowLastState = 0;
  for(int i=0; i<LED_NUM; i++){
    pinMode(BlueLED[i], OUTPUT);
    digitalWrite(BlueLED[i], LOW);
    pinMode(YellowLED[i], OUTPUT);
    digitalWrite(YellowLED[i], LOW);
  }
  pinMode (BLUE_SIG,INPUT);
  pinMode (YELLOW_SIG,INPUT);

}
void loop() {
//  YellowCount = 7;
//  BlueCount = 7;
//  ShowBlueLED();
//  ShowYellowLED();
//  while(1);
  CheckLight();
  ShowBlueLED();
  ShowYellowLED();
}

void CheckLight(){
  int BlueState = digitalRead(BLUE_SIG);
  int YellowState = digitalRead(YELLOW_SIG);
  if(BlueLastState == 0 && BlueState == 1){
    BlueCount++;
    BlueLastState = 1;
  }
  if(BlueState == 0){
    BlueLastState = 0;
  }
  if(YellowLastState == 0 && YellowState == 1){
    YellowCount++;
    YellowLastState = 1;
  }
  if(YellowState == 0){
    YellowLastState == 0;
  }
//  delay(2000);
}
void ShowBlueLED(){

  for(int i=0; i<BlueCount; i++){
    digitalWrite(BlueLED[i], HIGH);
  }
}
void ShowYellowLED(){

  for(int i=0; i<YellowCount; i++){
    digitalWrite(YellowLED[i], HIGH);
  }
}
