#pragma once

class CommunicatorSM
{
public:
    void runStateMachine();

private:
    int state;

    // Initilaize
    void state0();

    // Read
    void state1();

    // Write
    void state2();

};
