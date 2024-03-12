#include "robotActuation.h"

#include <iostream>
#include <string>

#include "communicator.h"

int main() 
{

    Communicator * c = new Communicator();
    RobotActuation * rbActuator = new RobotActuation("/dev/ttyACM0", 115200);
    std::cout << "connection made" << std::endl;

    rbActuator->sendDriveMotors(0, 0, 0, 0);
    rbActuator->sendCurrentQueue();
    rbActuator->run();

    RobotState lastState;
  while(true){
      std::cout << std::endl;
    c->readIncomingPacket();
    RobotState rbstate = c->getRobotState();

    if (lastState.flMotor != rbstate.flMotor || lastState.frMotor != rbstate.frMotor)
    {
          rbActuator->sendDriveMotors(rbstate.flMotor, rbstate.blMotor, rbstate.frMotor, rbstate.brMotor);
    }

    if (lastState.dumpMotor != rbstate.dumpMotor)
    {
      
      rbActuator->sendDumpMotor(rbstate.dumpMotor);
    }

    if (lastState.intakeMotor != rbstate.intakeMotor)
    {
      rbActuator->sendIntakeMotor(rbstate.intakeMotor);
    }

    if(lastState.intakeLocation != rbstate.intakeLocation)
    {
      rbActuator->sendIntakePosition(rbstate.intakeLocation);
    }

    rbActuator->sendCurrentQueue();
    rbActuator->run();

    lastState = rbstate;

  }

  return 0;
}


