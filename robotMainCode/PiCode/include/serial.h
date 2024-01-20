#ifndef SERIAL
#define SERIAL

#include <string>


class  serial
{

public:

  int handle;
  std::string  deviceName;
  int baud;

  serial(std::string deviceName, int baud);
  ~serial();

  bool Send( unsigned char  * data,int len);
  bool Send(unsigned char value);
  bool Send( std::string value);
  int Receive( unsigned char  * data, int len);
  bool IsOpen(void);
  void Close(void);
  bool Open(std::string deviceName, int baud);
  bool NumberByteRcv(int &bytelen);
};

#endif
