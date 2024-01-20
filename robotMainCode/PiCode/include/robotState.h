#include <bits/stdint-intn.h>
#include <mutex>
#pragma once

class RobotState
 {
 private:

   std::mutex classMutex;

   double batteryVoltage;

   uint8_t motorStates[8];

   // Forward motor values are 0, 256 with 128 being no motion

   // Driver motors
   uint8_t* flMotor;
   uint8_t* frMotor;
   uint8_t* brMotor;
   uint8_t* blMotor;

   uint8_t* intakeMotor;
   uint8_t* dumpMotor;

   uint8_t* lIntakeIndexer;
   uint8_t* rIntakeIndexer;

   int leftIntakeLoc;

 public:

   RobotState();

   double getBatteryVoltage();
   void setBatteryVoltage(double val);

   void setflMotor(uint8_t val);
   void setfrMotor(uint8_t val);
   void setblMotor(uint8_t val);
   void setbrMotor(uint8_t val);
   void setMotors(uint8_t flVal, uint8_t frVal, uint8_t blVal, uint8_t brVal);
   void setMotors(uint8_t lVal, uint8_t rVal);
   void setMotors(uint8_t val);

   void setIntakeMotor(uint8_t val);
   void setDumpMotor(uint8_t val);

   void setLIntakeIndexer(uint8_t val);
   void setRIntakeIndexer(uint8_t val);


  // Returns all motor status
   uint8_t*  getRobotState();

   void killAllMotion();
};
