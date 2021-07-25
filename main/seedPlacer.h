#pragma once
#include <Servo.h>
#include "myStepper.h"
#include "common.h"

class SeedPlacer{
  public:
    SeedPlacer();
    ~SeedPlacer();
    SeedPlacer(Servo servo, MyStepper stepper);
    void PlaceSeed();
    void PlaceNoSeed();
  private:
    void loadSeed();
    int count;
    Servo servo;
    MyStepper stepper;
};
