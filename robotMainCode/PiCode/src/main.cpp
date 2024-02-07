#include <iostream>
<<<<<<< HEAD
=======
#include "../include/robotControlSM.h"
#include "../include/communicatorSM.h"
#include "../include/serial.h"
>>>>>>> 8a15b4c2fe104e341fe6387a8cfe61d1fd246b7b
#include <unistd.h>

#include "../include/robotControlSM.h"
#include "../include/serial.h"
#include "../include/communicatorSM.h"



int main() {
<<<<<<< HEAD

  Communicator* com = new Communicator();




    // Serial serial("/dev/ttyACM0", 115200);
    //
    // // send info as a byte
    // int motorAmt = 0;
    // while (motorAmt < 256) {
    //   serial.Send(motorAmt);
    //   motorAmt++;
    //   usleep(100000);
    // }
    //
    // std::cout << "finished";
=======
  /*Serial serial("/dev/ttyACM0", 115200);

  // send info as a byte
  int motorAmt = 0;
  while (motorAmt < 256) {
    serial.Send(motorAmt);
    motorAmt++;
    usleep(100000);
  }

  std::cout << "finished";*/
>>>>>>> 8a15b4c2fe104e341fe6387a8cfe61d1fd246b7b

  CommunicatorSM robotComs;
  while (true) {
    robotComs.runStateMachine();
  }
  return 0;
}
