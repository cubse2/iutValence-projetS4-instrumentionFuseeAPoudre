#ifndef TimeStampedIMUData_h
#define TimeStampedIMUData_h

#include "IMUData.h"
#include <Arduino.h>


class TimeStampedIMUData : public IMUData
{
  private:
 
    unsigned long timestamp;
    
  public:
    TimeStampedIMUData(unsigned long theTime, XYZData acceleration, XYZData gyroscope,
    		XYZData magnetisme, float altitude):IMUData(acceleration, gyroscope, magnetisme, altitude);
    void setTimestamp(unsigned long theTime);
    void setTimeStampedIMUData(unsigned long theTime, XYZData *accelerationData, XYZData *gyroscopeData, 
      XYZData *magnetismData, float altitude);
    char* toChar();
};

#endif
