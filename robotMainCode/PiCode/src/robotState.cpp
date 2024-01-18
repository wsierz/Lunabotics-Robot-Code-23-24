#include "../include/robotState.h"

RobotState::RobotState()
{
    killAllMotion();
    flMotor = &motorStates[0];
    frMotor = &motorStates[1];
    blMotor = &motorStates[2];
    brMotor = &motorStates[3];
    intakeMotor = &motorStates[4];
    dumpMotor = &motorStates[5];
    lIntakeIndexer = &motorStates[6];
    rIntakeIndexer = &motorStates[7];
}


double RobotState::getBatteryVoltage()
{
    std::lock_guard<std::mutex> lk(classMutex);
    return batteryVoltage;
}

void RobotState::setBatteryVoltage(double val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    batteryVoltage = val;
}

void RobotState::setflMotor(int8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = val;
}

void RobotState::setfrMotor(int8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *frMotor = val;
}

void RobotState::setblMotor(int8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *blMotor = val;
}

void RobotState::setbrMotor(int8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *brMotor = val;
}
void RobotState::setMotors(int8_t flVal, int8_t frVal, int8_t blVal, int8_t brVal)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = flVal;
    *frMotor = frVal;
    *blMotor = blVal;
    *brMotor = brVal;
}
void RobotState::setMotors(int8_t lVal, int8_t rVal)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = lVal;
    *frMotor = rVal;
    *blMotor = lVal;
    *brMotor = rVal;
}
void RobotState::setMotors(int8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = val;
    *frMotor = val;
    *blMotor = val;
    *brMotor = val;
}

void RobotState::setIntakeMotor(int8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *intakeMotor = val;
}
void RobotState::setDumpMotor(int8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *dumpMotor = val;
}

void RobotState::setLIntakeIndexer(int8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *lIntakeIndexer = val;
}
void RobotState::setRIntakeIndexer(int8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *rIntakeIndexer= val;
}

// Returns 1 byte int array of all motor values to be sent
int8_t* RobotState::getRobotState()
{
    std::lock_guard<std::mutex> lk(classMutex);
    return motorStates;
}

void RobotState::killAllMotion()
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = 0;
    *frMotor = 0;
    *blMotor = 0;
    *brMotor = 0;
    *intakeMotor = 0;
    *dumpMotor = 0;
    *lIntakeIndexer = 0;
    *rIntakeIndexer = 0;
}
