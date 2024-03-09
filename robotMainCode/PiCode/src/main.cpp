#include "robotActuation.h"

#include <iostream>
#include <string>

#include "communicator.h"

int main() 
{
    Communicator * c = new Communicator();
    RobotActuation * rbActuator = new RobotActuation("/dev/ttyACM0", 115200);
    std::cout << "connection made" << std::endl;

    rbActuator->sendDriveMotors(100, 0, 0, 0);

  while(true){

    c->readIncomingPacket();
    std::cout << "Packet read" << std::endl;
    RobotState rbstate = c->getRobotState();

    std::cout << unsigned() << std::endl;

    rbActuator->sendDriveMotors(rbstate.flMotor, rbstate.blMotor, rbstate.frMotor, rbstate.brMotor);
    rbActuator->sendCurrentQueue();
    rbActuator->run();



  }
  // RobotActuation * rbActuator = new RobotActuation("/dev/ttyACM1", 115200);

  // rbActuator->sendDriveMotors(100, 0, 0, 0);

  // while(true)
  // {
  //   rbActuator->sendCurrentQueue();
  //   rbActuator->run();
  // }

  return 0;
}


