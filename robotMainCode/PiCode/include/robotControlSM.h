#pragma once
#include "robotState.h"
#include <iostream>


class RobotControlSM
 {
 private:

   bool running;
   int state;
   RobotState* rbState;

   // Initilazation state
   void state0();

   // Stop state
   void state1();

   // Teleop state
   void state2();

   // AutoState
   void state3();

   // Panic state
   void state4();


 public:
   void runStateMachine();
};
