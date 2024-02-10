#include "../include/communicator.h"

Communicator::Communicator()
{

}

bool Communicator::isDriverStationMessageRecived()
{
    return dsMessageRecived;
}

bool Communicator::isDriverStationStatusRecived()
{
    return dsStatusRecived;
}

std::bitset<DS_MESSAGE_LEN> Communicator::readDriverStationMessage()
{
    std::bitset<DS_MESSAGE_LEN> mess = dsMessageBuff.front();
    dsMessageBuff.pop();
    dsMessageRecived = !dsMessageBuff.empty();
    return mess;
}

std::bitset<DS_STAT_LEN> Communicator::readDriverStationStatus()
{
    std::bitset<DS_STAT_LEN> * messPointer = &dsStatusBuff[currDSStatusBuffPos%2];
    dsStatusRecived--;
    if (dsMessageRecived)
    {
        currDSStatusBuffPos++;
    }
    return *messPointer;
}


//TBD
bool Communicator::sendRobotState(std::bitset<ROB_STAT_LEN> message)
{
    return true;
}

void Communicator::loadDSStatus(std::bitset<DS_STAT_LEN> * mess)
{
    if (dsStatusRecived == 2)
    {
        currDSStatusBuffPos++;
        dsStatusBuff[currDSStatusBuffPos-1] = *mess;

    }
    else if (dsStatusRecived == 1)
    {
        dsStatusBuff[currDSStatusBuffPos-1] = *mess;
    }
    else
    {
        dsStatusBuff[currDSStatusBuffPos] = *mess;
        dsStatusRecived = true;
    }

}

void Communicator::loadDSMessage(std::bitset<DS_MESSAGE_LEN> * mess)
{
    dsMessageBuff.push(*mess);
}
