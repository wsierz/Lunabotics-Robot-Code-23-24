#include <bits/stdint-intn.h>
#include <mutex>
#pragma once

class RobotState
 {
 private:

   std::mutex classMutex;

   double batteryVoltage;

   int8_t motorStates[8];

   // All motor values in speed from -128 to 127 (8 bits)

   // Driver motors
   int8_t* flMotor;
   int8_t* frMotor;
   int8_t* brMotor;
   int8_t* blMotor;

   int8_t* intakeMotor;
   int8_t* dumpMotor;

   int8_t* lIntakeIndexer;
   int8_t* rIntakeIndexer;

   int leftIntakeLoc;

 public:

   RobotState();

   double getBatteryVoltage();
   void setBatteryVoltage(double val);

   void setflMotor(int8_t val);
   void setfrMotor(int8_t val);
   void setblMotor(int8_t val);
   void setbrMotor(int8_t val);
   void setMotors(int8_t flVal, int8_t frVal, int8_t blVal, int8_t brVal);
   void setMotors(int8_t lVal, int8_t rVal);
   void setMotors(int8_t val);

   void setIntakeMotor(int8_t val);
   void setDumpMotor(int8_t val);

   void setLIntakeIndexer(int8_t val);
   void setRIntakeIndexer(int8_t val);


  // Returns all motor status
   int8_t*  getRobotState();

   void killAllMotion();
};
