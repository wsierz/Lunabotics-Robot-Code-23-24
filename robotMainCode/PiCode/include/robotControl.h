#include <bits/stdint-intn.h>

#include "communicator.h"
#include "robotActuation.h"

#pragma once

struct RobotState {

    //These values are 0 - 4095 (12 bits). Thse actual angle is loc*360/4096
    uint16_t intakeLocation;

    // All motors are -100 to 100
    // Driver motors
    int8_t flMotor;
    int8_t frMotor;
    int8_t brMotor;
    int8_t blMotor;

    int8_t intakeMotor;
    int8_t dumpMotor;
};

class RobotControl{
private:
    double batteryVoltage;
    Communicator* communicator;

    RobotActuation* robotActuation;

    RobotState desiedState;
    RobotState trueState;


    /**
     * @brief Holds the state the robot is currently in
     *   0 = robotStartup
     *   1 = stopState
     *   2 = teleopState
     *   3 = autoState (Not yet defined)
     *   -1 = panic!
     */
    int currentState;
    bool running;

public:

    int robotStartup();

    int robotRunStateMachine();

    int runStartupState();

    int runStopState();

    int runTeleopState();

    int runAutoState();

    int runPanicState();

    int setRobotState(int8_t flMotor);

    int setDriveValues(int8_t flVal, int8_t frVal, int8_t blVal, int8_t brVal);

    int setIntakeSpeed(int8_t val);

    int setDumpSpeed(int8_t val);

    int setIntakePosition(int8_t val);
};
