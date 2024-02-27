#include "robotActuation.h"
#include <iostream>

/**
 * @brief Constructor
 * @param port The port the adafruit feather is expected on
 * @param baud_rate Baud_rate for the communication (should be 115200 per specification)
 */
RobotActuation::RobotActuation(std::string port, unsigned int baud_rate) : io(), serial(io, port)
{
    serial.set_option(asio::serial_port_base::baud_rate(baud_rate));
}

void RobotActuation::readNextMessage()
{

}

void RobotActuation::sendDriveMotors(int8_t frontLeftMotor, int8_t frontRightMotor, int8_t backLeftMotor, int8_t backRightMotor)
{
    SerialPacket packet = {0xBE, 0xEF};

    packet.portions.messageType = 0x81;

    packet.portions.data[0] = frontLeftMotor;
    packet.portions.data[1] = frontRightMotor;
    packet.portions.data[2] = backLeftMotor;
    packet.portions.data[3] = backRightMotor;

    enqueueMessage(&packet);
}

int RobotActuation::sendCurrentQueue()
{
    if (byteQueueFull && !serialTransmit)
    {
        serialTransmit = true;
        serial.async_write_some(asio::buffer(outgoingBytes, SERIAL_MES_LEN),
         [this](const asio::error_code& error, std::size_t bytes_transferred) 
         {
            sendBytesHandler(error, bytes_transferred);
         }
        );
        byteQueueFull = false;
    }
    if (!byteQueueFull && !outgoingQueue.empty())
    {
        SerialPacket * packet = &outgoingQueue.front();
        addChecksum(packet);

        std::copy(std::begin(packet->packet), std::end(packet->packet), outgoingBytes);
        outgoingQueue.pop();
        std::cout << outgoingQueue.front().portions.messageType;
        byteQueueFull = true;
    }
    return 0;
}

void RobotActuation::sendBytesHandler(const asio::error_code& error, std::size_t bytes_transferred)
{
    std::cout << "Sent" << std::endl;
    positonOfNextOutgoingByte += bytes_transferred;
    if (positonOfNextOutgoingByte >= SERIAL_MES_LEN)
    {
        byteQueueFull = false;
        serialTransmit = false;
        positonOfNextOutgoingByte = 0;
    }
}

void RobotActuation::run()
{
    io.reset();
    io.run();
}

void RobotActuation::reciveMessageHandler()
{

}

void RobotActuation::enqueueMessage(SerialPacket *mess)
{
    outgoingQueue.push(*mess);
}

void RobotActuation::addChecksum(SerialPacket * packet)
{
    uint8_t * ptr = packet->packet;
    packet->portions.checksum = fletcher16(ptr, SERIAL_MES_LEN-2);
}


uint16_t RobotActuation::fletcher16(const uint8_t *data, size_t len) {
	uint32_t c0, c1;

	/*  Found by solving for c1 overflow: */
	/* n > 0 and n * (n+1) / 2 * (2^8-1) < (2^32-1). */
	for (c0 = c1 = 0; len > 0; ) {
		size_t blocklen = len;
		if (blocklen > 5802) {
			blocklen = 5802;
		}
		len -= blocklen;
		do {
			c0 = c0 + *data++;
			c1 = c1 + c0;
		} while (--blocklen);
		c0 = c0 % 255;
		c1 = c1 % 255;
   }
   return (c1 << 8 | c0);
}


