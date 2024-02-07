#include <iostream>
#include <unistd.h>

#include "../include/robotControlSM.h"
#include "../include/serial.h"
#include "../include/communicatorSM.h"



int main() {

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

    return 0;
}
