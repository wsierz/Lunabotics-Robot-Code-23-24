#include "robotActuation.h"

#include <iostream>
#include <string>


int main() {

  RobotActuation * rbActuator = new RobotActuation("/dev/ttyACM0", 115200);

  rbActuator->sendDriveMotors(-100, -100, -100, -100);

  while(true)
  {
    rbActuator->sendCurrentQueue();
    rbActuator->run();
  }

  return 0;
}


