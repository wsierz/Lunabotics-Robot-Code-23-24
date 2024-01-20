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

void RobotState::setflMotor(uint8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = val;
}

void RobotState::setfrMotor(uint8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *frMotor = val;
}

void RobotState::setblMotor(uint8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *blMotor = val;
}

void RobotState::setbrMotor(uint8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *brMotor = val;
}
void RobotState::setMotors(uint8_t flVal, uint8_t frVal, uint8_t blVal, uint8_t brVal)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = flVal;
    *frMotor = frVal;
    *blMotor = blVal;
    *brMotor = brVal;
}
void RobotState::setMotors(uint8_t lVal, uint8_t rVal)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = lVal;
    *frMotor = rVal;
    *blMotor = lVal;
    *brMotor = rVal;
}
void RobotState::setMotors(uint8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = val;
    *frMotor = val;
    *blMotor = val;
    *brMotor = val;
}

void RobotState::setIntakeMotor(uint8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *intakeMotor = val;
}
void RobotState::setDumpMotor(uint8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *dumpMotor = val;
}

void RobotState::setLIntakeIndexer(uint8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *lIntakeIndexer = val;
}
void RobotState::setRIntakeIndexer(uint8_t val)
{
    std::lock_guard<std::mutex> lk(classMutex);
    *rIntakeIndexer= val;
}

// Returns 1 byte int array of all motor values to be sent
uint8_t* RobotState::getRobotState()
{
    std::lock_guard<std::mutex> lk(classMutex);
    return motorStates;
}

void RobotState::killAllMotion()
{
    std::lock_guard<std::mutex> lk(classMutex);
    *flMotor = 128;
    *frMotor = 128;
    *blMotor = 128;
    *brMotor = 128;
    *intakeMotor = 128;
    *dumpMotor = 128;
    *lIntakeIndexer = 128;
    *rIntakeIndexer = 128;
}
