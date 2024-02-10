#include <iostream>
#include "../include/robotControlSM.h"
#include "../include/communicatorSM.h"
#include "../include/serial.h"
#include <unistd.h>

#include "../include/robotControlSM.h"
#include "../include/serial.h"
#include "../include/communicatorSM.h"



int main() {
  Serial serial("/dev/ttyACM0", 115200);

  // send info as a string
  std::string data = "m255m255";
  while (true) {
    serial.Send(data);
    usleep(100000);
  }

  std::cout << "finished";

  /*CommunicatorSM robotComs;
  while (true) {
    robotComs.runStateMachine();
  }*/
  return 0;
}
