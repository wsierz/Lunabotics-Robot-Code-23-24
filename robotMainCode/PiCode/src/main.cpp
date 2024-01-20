#include <iostream>
#include "../include/robotControlSM.h"
#include "serial.h"
#include <stdio.h>
#include <stdint.h>
using namespace std;

int main() {
    Serial serial("/dev/ttyACM0", 115200);

    // send info as a byte
    uint8_t motorAmt = 0;
    while (true) {
      scanf(" %d", &motorAmt);
      serial.Send(motorAmt);
      cout<<motorAmt;
    }

    cout << "finished";

    return 0;
}