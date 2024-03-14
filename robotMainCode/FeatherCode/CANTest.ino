// /*
//  * Adafruit MCP2515 FeatherWing CAN Sender Example
//  */

// #include <Adafruit_MCP2515.h>

// #define CAN_ID_MANUFACTURER_REV 5
// #define CAN_ID_DEVICE_TYPE_MOTOR_CONTROLLER 2

// #define SPARK_MAX_API_CLASS_DUTY_CYCLE 0
// #define SPARK_MAX_API_CLASS_HEARTBEAT 9

// #define SPARK_MAX_API_INDEX_DUTY_CYCLE 2
// #define SPARK_MAX_API_INDEX_HEARTBEAT 2

// #define SPARK_MAX_ID_MAX 31

// // Set CAN bus baud rate
// #define CAN_BAUDRATE (1000000)

// Adafruit_MCP2515 mcp(PIN_CAN_CS);

// bool SparkMaxEnabled[SPARK_MAX_ID_MAX];

// void setup() {
//   delay(1000);
//   Serial.begin(115200);
//   while(!Serial) delay(10);

//   Serial.println("MCP2515 Sender test setup!");
//   Serial.print("CAN ID: ");
//   Serial.println(CreateSparkMaxID(SPARK_MAX_API_CLASS_DUTY_CYCLE, SPARK_MAX_API_INDEX_DUTY_CYCLE, 9), 16);

//   if (!mcp.begin(CAN_BAUDRATE)) {
//     Serial.println("Error initializing MCP2515.");
//     while(1) delay(10);
//   }
//   Serial.println("MCP2515 chip found");

//   for(int i = 0; i < SPARK_MAX_ID_MAX; i++) {
//     SetSparkMaxEnabled(i, false);
//   }

//   SetSparkMaxEnabled(9, true);
//   Serial.println("Setup finished!");
// }

// typedef union
// {
//   float number;
//   uint8_t bytes[4];
// } float_union_t;

// void loop() {
//   float_union_t speed;
//   speed.number = 0.1;

//   Serial.println("loop 1");
//   SendSparkMaxSpeed(9, 0.1);
//   Serial.println("loop 2");

//   delay(10);

//   SendSparkMaxHeartbeat();
//   Serial.println("loop 3");

//   delay(1000);

// }

// uint32_t CreateSparkMaxID(int api_class, int api_index, int device_id) {
//   uint32_t device_id_bits = device_id & 0x3F; // Bits [0-5] are the device ID
//   uint32_t api_index_bits = (api_index & 0x0F) << 6; // Bits [6-9] are the API index
//   uint32_t api_class_bits = (api_class & 0x3F) << 10; // Bits [10-15] are the API class
//   uint32_t manufacturer_id_bits = (CAN_ID_MANUFACTURER_REV & 0xFF) << 16;
//   uint32_t device_type_bits  = (CAN_ID_DEVICE_TYPE_MOTOR_CONTROLLER & 0x1F) << 24;
//   uint32_t id = device_id_bits | api_index_bits | api_class_bits | manufacturer_id_bits | device_type_bits;

//   return id;
// }

// void SendSparkMaxSpeed(int motorID, float speed) {
//   float_union_t speed_bytes;
//   speed_bytes.number = speed;

//   uint32_t packetID = CreateSparkMaxID(SPARK_MAX_API_CLASS_DUTY_CYCLE, SPARK_MAX_API_INDEX_DUTY_CYCLE, motorID);
//   mcp.beginExtendedPacket(packetID);
//   mcp.write(speed_bytes.bytes[0]);
//   mcp.write(speed_bytes.bytes[1]);
//   mcp.write(speed_bytes.bytes[2]);
//   mcp.write(speed_bytes.bytes[3]);
//   mcp.write(0x00);
//   mcp.write(0x00);
//   mcp.write(0x00);
//   mcp.write(0x00);
//   mcp.endPacket();
// }

// void SendSparkMaxHeartbeat() {
//   uint32_t packetID = CreateSparkMaxID(SPARK_MAX_API_CLASS_HEARTBEAT, SPARK_MAX_API_INDEX_HEARTBEAT, 0); 
//   uint8_t bytes[8] = {0, 0};

//   for(int i = 0; i < SPARK_MAX_ID_MAX; i++) {
//     int byte = i / 8;
//     int bit = i % 8;

//     if(SparkMaxEnabled[i]) {
//       bytes[byte] |= (0x01 << bit);
//     }
//   }

//   mcp.beginExtendedPacket(packetID);
//   for(int i = 0; i < 8; i++) {
//     mcp.write(bytes[i]);
//   }
//   mcp.endPacket();
// }

// void SetSparkMaxEnabled(int device_id, bool enabled) {
//   SparkMaxEnabled[device_id] = enabled;
// }