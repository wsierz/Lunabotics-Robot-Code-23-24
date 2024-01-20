#include <iostream>
#include "../include/robotControlSM.h"
#include "../include/serial.h"
#include <unistd.h>

int main() {
    Serial serial("/dev/ttyACM0", 115200);

    // send info as a byte
    int motorAmt = 0;
    while (motorAmt < 256) {
      serial.Send(motorAmt);
      motorAmt++;
      usleep(100000);
    }

    std::cout << "finished";

    return 0;
}
