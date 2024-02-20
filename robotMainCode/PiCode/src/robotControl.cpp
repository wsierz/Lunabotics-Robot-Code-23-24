#include "../include/robotControl.h"

int RobotControl::robotRunStateMachine()
{
    while(running) {
        switch (currentState)
        {
            case 0:
                runStartupState();
                break;
            case 1:
                runStopState();
                break;
            case 2:
                runTeleopState();
                break;
            case 3:
                runAutoState();
            default:
                runPanicState();

        }
    }
    return 1;
}

int RobotControl::robotStartup()
{
    return robotRunStateMachine();
}

int RobotControl::runStartupState()
{
    return 1;
}


int RobotControl::runAutoState()
{
    currentState = -1;
    return 1;
}

int RobotControl::runStopState()
{
    setDriveValues(0,0,0,0);
    setIntakeSpeed(0);
    setDumpSpeed(0);
    setIntakePosition(trueState.intakeLocation);


    return 1;
}

int RobotControl::runTeleopState()
{
    return 1;
}

int RobotControl::runPanicState()
{
    // Robot is paniced!
    setDriveValues(0,0,0,0);
    setIntakeSpeed(0);
    setDumpSpeed(0);
    setIntakePosition(trueState.intakeLocation);
    currentState = -1;

    return -1;
}
