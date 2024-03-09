#include "communicator.h"


Communicator::Communicator(): io(), socket(io),
    acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 2000))
{
    acceptor.accept(socket);

}

void Communicator::readIncomingPacket()
{
    asio::read(socket, asio::buffer(data, MESS_0x01_LEN));
    //asio::read_until( socket, incomingBuffer, "/n" );
    proccesMessage();
    
}

void Communicator::send(asio::ip::tcp::socket &socket, const std::string &message)
{
    const std::string msg = message + "\n";
    asio::write( socket, asio::buffer(message) );
}

RobotState Communicator::getRobotState()
{
    const std::lock_guard<std::mutex> lock(mutex);
    return rbState;
}

void Communicator::proccesMessage()
{
    // //const std::lock_guard<std::mutex> lock(mutex);

    // incomingBuffer.commit(MESS_0x01_LEN);

    // std::istream is(&incomingBuffer);
    // std::string s;
    // is >> s;

    // uint8_t data[s.length() + 1];
	// strcpy((char*)data, s.c_str()); 

    
    for (int i = 0; i < MESS_0x01_LEN; i++)
    {
        std::cout <<std::hex<< unsigned(data[i]);
    }
    std::cout << std::endl;

    if(data[0] == 0x01)
    {
        std::cout << "Correct Packet Type" << std::endl;
        processControllerState(data);
        incomingBuffer.consume(MESS_0x01_LEN);
    }

    
}

void Communicator::processControllerState(uint8_t* data)
{
    rbState.flMotor = data[1];
    rbState.blMotor = data[1];

    rbState.frMotor = data[3];
    rbState.brMotor = data[3];
}
