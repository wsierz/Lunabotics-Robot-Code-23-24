#include "robotActuation.h"

#include <iostream>
#include <string>


int main() 
{

  RobotActuation * rbActuator = new RobotActuation("/dev/ttyACM1", 115200);

  rbActuator->sendDriveMotors(100, 0, 0, 0);

  while(true)
  {
    rbActuator->sendCurrentQueue();
    rbActuator->run();
  }

  return 0;
}


