#include "../include/robotControlSM.h"
#include <iostream>

void RobotControlSM::runStateMachine()
{
    running = true;
    state = 0;
    while (running)
    {
        switch (state)
        {
            case 0:
                state0();
            case 1:
                state1();
            case 2:
                state2();
            case 3:
                state3();
            case 4:
                state4();
            default:
                state4(); // Panic if enter null state

        }
    }

    //Shut down robot?

}

// Startup state
void RobotControlSM::state0()
{
    // Start up needed values
    rbState = new RobotState;


    // move on to state 1
    state = 1;
}

// Rest State
void RobotControlSM::state1()
{
    rbState->killAllMotion();

    // Wait until signal recivied to enter next state
}

// Teleop state
void RobotControlSM::state2()
{
    // connect comm protocol to the rb state
}

// Auto state
void RobotControlSM::state3()
{
    // Connect the auto protocol to the comm state
}

// Panic state
void RobotControlSM::state4()
{
    std::cout << "Panic State Enetered! Please read logs" << std::endl;
    rbState->killAllMotion();
    running = false;
}



