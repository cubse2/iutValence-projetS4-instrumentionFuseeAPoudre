#ifndef TimeStampedIMUData_h
#define TimeStampedIMUData_h

#include "IMUData.h"
#include <Arduino.h>


class TimeStampedIMUData : public IMUData
{
  private:
 
    unsigned long timestamp;
    
  public:
    TimeStampedIMUData(XYZData acceleration, XYZData gyroscope,
    		XYZData magnetisme, float pressure, unsigned long time):IMUData(acceleration, gyroscope, magnetisme, pressure);
    char* toChar();
};

#endif
