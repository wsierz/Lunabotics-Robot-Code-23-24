#include "communicatorSM.h"
#include "robotActuation.h"

#include <iostream>
#include <string>


void handler(  const asio::error_code& error, std::size_t bytes_transferred)
{
    std::cout << "sIt worked!";
}

int main() {
  std::cout << "Robot starting up...\n";


  asio::io_service io;

  asio::serial_port serial(io);

  serial.open("/dev/pts/6");

  //asio::write(serial, asio::buffer("TestTestTest"));

  asio::async_write(serial, asio::buffer("TestTestTest\n"), handler);

  while(true);
  return 0;
}


