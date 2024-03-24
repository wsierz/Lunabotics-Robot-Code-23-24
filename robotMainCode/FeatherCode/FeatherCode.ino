#include <Servo.h>
#include <Adafruit_MCP2515.h>
extern "C" {
#include "pico/bootrom.h"
}

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

#define CAN_ID_MANUFACTURER_REV 5
#define CAN_ID_DEVICE_TYPE_MOTOR_CONTROLLER 2

#define SPARK_MAX_API_CLASS_DUTY_CYCLE 0
#define SPARK_MAX_API_CLASS_HEARTBEAT 9

#define SPARK_MAX_API_INDEX_DUTY_CYCLE 2
#define SPARK_MAX_API_INDEX_HEARTBEAT 2

#define SPARK_MAX_ID_MAX 31

#define ROBOT_TIMEOUT_MS (2 * 1000)

// Set CAN bus baud rate
#define CAN_BAUDRATE (1000000)
Adafruit_MCP2515 mcp(PIN_CAN_CS);

const int FRONT_LEFT_MOTOR_PIN = 25;
const int BACK_LEFT_MOTOR_PIN = 9;
const int FRONT_RIGHT_MOTOR_PIN = 27;
const int BACK_RIGHT_MOTOR_PIN = 29;
const int DEPLOY_MOTOR_PIN = 11;

const int INTAKE_MOTOR_CAN_ID = 9;
const int DUMP_MOTOR_CAN_ID = 10;

Servo frontLeftMotor;
Servo backLeftMotor;
Servo frontRightMotor;
Servo backRightMotor;
Servo deployMotor;

const int PACKET_SIZE = 13;
const int BUFFER_SIZE = 1;

uint8_t packet[PACKET_SIZE];
int currentIndex = 0;

const int INDEX_NO_PACKET = -1;

bool SparkMaxEnabled[SPARK_MAX_ID_MAX];
float intakeSpeed = 0.0;
float dumpSpeed = 0.0;

unsigned long lastPacket;

void setup() {
  Serial.begin(115200);
  while(!Serial) delay(10);

  Serial.println("MCP2515 Sender test setup!");
  if (!mcp.begin(CAN_BAUDRATE)) {
    Serial.println("Error initializing MCP2515.");
    while(1) delay(10);
  }
  Serial.println("MCP2515 chip found");

  frontLeftMotor.attach(FRONT_LEFT_MOTOR_PIN);
  backLeftMotor.attach(BACK_LEFT_MOTOR_PIN);
  frontRightMotor.attach(FRONT_RIGHT_MOTOR_PIN);
  backRightMotor.attach(BACK_RIGHT_MOTOR_PIN);
  deployMotor.attach(DEPLOY_MOTOR_PIN);

  for(int i = 0; i < SPARK_MAX_ID_MAX; i++) {
    SetSparkMaxEnabled(i, false);
  }
  Serial.println("Setup complete");
}

void loop() {
  updateSerial();

  if(millis() - lastPacket > ROBOT_TIMEOUT_MS) {
    intakeSpeed = 0.0;
    SendSparkMaxSpeed(INTAKE_MOTOR_CAN_ID, 0.0);
    delay(5);
    SendSparkMaxSpeed(DUMP_MOTOR_CAN_ID, 0.0);
    SetDriveMotors(0, 0, 0, 0);
    SetDeployMotor(0);
    
    for(int i = 0; i < SPARK_MAX_ID_MAX; i++) {
      SetSparkMaxEnabled(i, false);
    }
  }

  delay(10); // Note: we need a delay in between CAN packets
  SendSparkMaxHeartbeat();
}

void updateSerial() {
  if (!Serial.available()) {
    return;
  }
  //is data available
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
      Serial.println("Packet Received");
      processPacket();
      currentIndex = 0;
    }
  }
}

void processPacket()
{
  // Ensure matching checksum, else return from function call. 
  if (!verifyChecksum)
  {
    Serial.println("Bad checksum");
    return;
  }

  lastPacket = millis();

  // Packet has a valid checksum, now process

  switch (packet[2]) {
    case 0x81:
      handleSetDriverMotorPacket();
      break;
    case 0x83:
      handleSetIntakeSpeedPacket();
      break;
    case 0x84: 
      handleSetDumpSpeedPacket();
      break;
    case 0x82:
      SetDeployMotor((int8_t) packet[3]);
      break;
    case 0xA0:
      Serial.println("Enter bootloader Mode"); 
      reset_usb_boot(1 << LED_BUILTIN, 0);
      break;
  }
}

void handleSetDumpSpeedPacket() {
  uint8_t speed = packet[3];

  intakeSpeed = -((float) speed) / 100.0;
  Serial.println("Set dump speed");
  SendSparkMaxSpeed(DUMP_MOTOR_CAN_ID, intakeSpeed);
  delay(1);
  SetSparkMaxEnabled(DUMP_MOTOR_CAN_ID, true);
}

void handleSetIntakeSpeedPacket() {
  uint8_t speed = packet[3];

  intakeSpeed = -((float) speed) / 100.0;
  Serial.println("Set intake speed");
  SendSparkMaxSpeed(INTAKE_MOTOR_CAN_ID, intakeSpeed);
  delay(1);
  SetSparkMaxEnabled(INTAKE_MOTOR_CAN_ID, true);
}

void handleSetDriverMotorPacket()
{
  SetDriveMotors((int8_t)packet[3], (int8_t)packet[4], (int8_t)packet[5], (int8_t)packet[6]);
}

void SetDriveMotors(int8_t frontLeft, int8_t frontRight, int8_t backLeft, int8_t backRight) {
  Serial.printf("Set Drive Motors: FL=%d FR=%d BL=%d BR=%d\n", frontLeft, frontRight, backLeft, backRight);
  frontLeftMotor.writeMicroseconds(map(frontLeft, -100, 100, 1000, 2000));
  frontRightMotor.writeMicroseconds(map(-frontRight, -100, 100, 1000, 2000));
  backLeftMotor.writeMicroseconds(map(backLeft, -100, 100, 1000, 2000));
  backRightMotor.writeMicroseconds(map(-backRight, -100, 100, 1000, 2000));
}

void SetDeployMotor(int8_t speed) {
  deployMotor.writeMicroseconds(map(-speed, -100, 100, 1000, 2000));
  Serial.printf("Set Deploy Motor: %d\n", speed);
}

inline bool verifyChecksum()
{
   uint16_t correctChecksum = fletcher16(packet, PACKET_SIZE-2);
  uint8_t lowChecksumByte = correctChecksum & 0xff;
  uint8_t highChecksumByte = (correctChecksum>> 8) & 0xff;

  return  lowChecksumByte == packet[12] && highChecksumByte == packet[11];
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

typedef union
{
  float number;
  uint8_t bytes[4];
} float_union_t;

uint32_t CreateSparkMaxID(int api_class, int api_index, int device_id) {
  uint32_t device_id_bits = device_id & 0x3F; // Bits [0-5] are the device ID
  uint32_t api_index_bits = (api_index & 0x0F) << 6; // Bits [6-9] are the API index
  uint32_t api_class_bits = (api_class & 0x3F) << 10; // Bits [10-15] are the API class
  uint32_t manufacturer_id_bits = (CAN_ID_MANUFACTURER_REV & 0xFF) << 16;
  uint32_t device_type_bits  = (CAN_ID_DEVICE_TYPE_MOTOR_CONTROLLER & 0x1F) << 24;
  uint32_t id = device_id_bits | api_index_bits | api_class_bits | manufacturer_id_bits | device_type_bits;

  return id;
}

void SendSparkMaxSpeed(int motorID, float speed) {
  float_union_t speed_bytes;
  speed_bytes.number = speed;

  uint32_t packetID = CreateSparkMaxID(SPARK_MAX_API_CLASS_DUTY_CYCLE, SPARK_MAX_API_INDEX_DUTY_CYCLE, motorID);
  mcp.beginExtendedPacket(packetID);
  mcp.write(speed_bytes.bytes[0]);
  mcp.write(speed_bytes.bytes[1]);
  mcp.write(speed_bytes.bytes[2]);
  mcp.write(speed_bytes.bytes[3]);
  mcp.write(0x00);
  mcp.write(0x00);
  mcp.write(0x00);
  mcp.write(0x00);
  mcp.endPacket();
}

void SendSparkMaxHeartbeat() {
  uint32_t packetID = CreateSparkMaxID(SPARK_MAX_API_CLASS_HEARTBEAT, SPARK_MAX_API_INDEX_HEARTBEAT, 0); 
  uint8_t bytes[8] = {0, 0};

  for(int i = 0; i < SPARK_MAX_ID_MAX; i++) {
    int byte = i / 8;
    int bit = i % 8;

    if(SparkMaxEnabled[i]) {
      bytes[byte] |= (0x01 << bit);
    }
  }

  mcp.beginExtendedPacket(packetID);
  for(int i = 0; i < 8; i++) {
    mcp.write(bytes[i]);
  }
  mcp.endPacket();
}

void SetSparkMaxEnabled(int device_id, bool enabled) {
  SparkMaxEnabled[device_id] = enabled;
}