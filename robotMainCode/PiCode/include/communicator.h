#pragma once
#include <bitset>
#include <mutex>
#include <queue>

// Defines driver station status length
#define DS_STAT_LEN 32
// Defines driver station message length
#define DS_MESSAGE_LEN 32
// Defines robot status message length
#define ROB_STAT_LEN 32
#define MAX_QUEUE_LEN 15

class Communicator
{
private:
    bool dsMessageRecived;
    int dsStatusRecived;

    std::bitset<DS_STAT_LEN> dsStatusBuff[2];
    std::queue<std::bitset<DS_MESSAGE_LEN>> dsMessageBuff;
    std::bitset<ROB_STAT_LEN> robStatusBuff[2];

    int currDSStatusBuffPos;
    int currRobStatusBuffPos;

    void loadDSStatus(std::bitset<DS_STAT_LEN> * mess);
    void loadDSMessage(std::bitset<DS_MESSAGE_LEN> * mess);

    std::mutex classMutex;



    

public:
    Communicator();

    // Sends the robot status message to the driver station. Defined in documentation
    bool sendRobotState(std::bitset<ROB_STAT_LEN> message);

    // Used to send direct robot messages outside of controller status
    bool isDriverStationMessageRecived();
    std::bitset<DS_MESSAGE_LEN> readDriverStationMessage();

    // Used to flag and to read from driver station message. Only the last message is read. If another packet arrices before this one is handled, it is replaced by the new one.
    bool isDriverStationStatusRecived();
    std::bitset<DS_STAT_LEN> readDriverStationStatus();
};
