#include "robotActuation.h"


/**
 * @brief Constructor
 * @param port The port the adafruit feather is expected on
 * @param baud_rate Baud_rate for the communication (should be 115200 per specification)
 */
RobotActuation::RobotActuation(std::string port, unsigned int baud_rate) : io(), serial(io,port)
{
    serial.set_option(asio::serial_port_base::baud_rate(baud_rate));
}

void RobotActuation::enqueueMessage()
{
    
}

void RobotActuation::readNextMessage()
{

}
