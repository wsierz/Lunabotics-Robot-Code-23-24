#pragma once

#include "asio.hpp"
#include <queue>

 // This class will use the Adafruit feather to acutaly control the robot based on Robot state. This is TBD

class RobotActuation{

struct OutgoingMessage
{

};

public:
    RobotActuation(std::string port, unsigned int baud_rate);
    void enqueueMessage();
    void readNextMessage();

private:

    asio::io_service io;
    asio::serial_port serial;

    std::queue<OutgoingMessage> outgoingQueue;

    void sendMessageHandler();
    void reciveMessageHandler();

};
