#include <Servo.h>

// const int BUFFER_SIZE = 1;
// char buf[BUFFER_SIZE];

// Servo test;

// void setup() {
//   Serial.begin(115200);
//   test.attach(5);
// }

// int speed;

// void loop() {
//   if (Serial.available())
//   {
//     Serial.readBytes(buf, BUFFER_SIZE);
//     speed = map(buf[0], 0, 256, 1000, 2000);
//     test.writeMicroseconds(speed);
//   }
// }

#include <stdint.h>

const int FRONT_LEFT_MOTOR_PIN = 4;
const int BACK_LEFT_MOTOR_PIN = 8;
const int FRONT_RIGHT_MOTOR_PIN = 8;
const int BACK_RIGHT_MOTOR_PIN = 8;

Servo frontLeftMotor;
Servo backLeftMotor;
Servo frontRightMotor;
Servo backRightMotor;

const int PACKET_SIZE = 13;
const int BUFFER_SIZE = 1;

uint8_t packet[PACKET_SIZE];
int currentIndex = 0;

const int INDEX_NO_PACKET = -1;

void setup() {
  Serial.begin(115200);

  frontLeftMotor.attach(FRONT_LEFT_MOTOR_PIN);
  backLeftMotor.attach(BACK_LEFT_MOTOR_PIN);
  frontRightMotor.attach(FRONT_RIGHT_MOTOR_PIN);
  backRightMotor.attach(BACK_RIGHT_MOTOR_PIN);
}

void loop() {
  update();
}

void update() {

  if (!Serial.available()) {
    return;
  }
  //is data abailable
  uint8_t incomingByte = Serial.read();
  //check if we are reading a packet
  if (currentIndex == INDEX_NO_PACKET) {
    //check if it is the sync byte(0xBE)
    if (incomingByte == 0xBE) {
      //set the index to 0
      currentIndex = 0;
      //add this to the packet array
      packet[currentIndex++] = incomingByte;
    }
  } else {
    if (currentIndex == 1) {
      if (incomingByte != 0xEF) {
        currentIndex = INDEX_NO_PACKET;
        return;
      }
    }
    packet[currentIndex++] = incomingByte;
    if (currentIndex >= PACKET_SIZE) {
      //do something with that packet
      processPacket;
      Serial.print("Packet Received");
      currentIndex = 0;
    }
  }
  // Update motors and send motor ack if needed
  // Send heartbeat if needed
  // Send telemetry data
} 

void processPacket()
{
  uint16_t correctChecksum = fletcher16(packet, PACKET_SIZE);
  uint8_t lowChecksumByte = correctChecksum & 0xff;
  uint8_t highChecksumByte = correctChecksum >> 8;

  // Ensure matching checksum, else return from function call. 
  if (!verifyChecksum)
  {
    return;
  }

  // Packet has a valid checksum, now process

  switch (packet[2]) {
    case 0x81:
      setDriveMotors();
  }
}

inline void setDriveMotors()
{
    frontLeftMotor.writeMicroseconds(map(packet[3], -100, 100, 1500, 2000));
    frontRightMotor.writeMicroseconds(map(packet[4], -100, 100, 1500, 2000));
    backLeftMotor.writeMicroseconds(map(packet[5], -100, 100, 1500, 2000));
    backRightMotor.writeMicroseconds(map(packet[6], -100, 100, 1500, 2000));
}

inline bool verifyChecksum()
{
  uint16_t correctChecksum = fletcher16(packet, PACKET_SIZE-2);
  uint8_t lowChecksumByte = correctChecksum & 0xff;
  uint8_t highChecksumByte = correctChecksum>> 8;

  return  lowChecksumByte == packet[1] && highChecksumByte == packet[0];
}

uint16_t fletcher16(const uint8_t *data, size_t len) {
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