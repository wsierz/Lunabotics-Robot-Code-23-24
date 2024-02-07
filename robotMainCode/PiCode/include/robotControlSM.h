#pragma once
#include "robotState.h"
#include "communicator.h"
#include "robotActuation.h"
#include <chrono>

#include <iostream>

class RobotControlSM
 {
 private:

   bool running;
   int state;
   RobotState* rbState;
   Communicator* communicator;
   RobotActuation* robotAcuator;
   uint64_t lastStatusSentTime;
   const int heartBeatInterval = 500; // In millis

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

   uint64_t getTime();

   void sendStatus();

 public:
   void runStateMachine();
};
