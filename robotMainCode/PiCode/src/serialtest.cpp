#include "serial.h"
#include <iostream>
using namespace std;

int main() {
    serial testSerial("/dev/ttyAMA0", 115200);

    // send info as a byte
    testSerial.Send(128);
    testSerial.Send(255);

    cout << "finished";

    return 0;
}