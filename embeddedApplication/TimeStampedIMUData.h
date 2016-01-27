#ifndef TimeStampedIMUData_h
#define TimeStampedIMUData_h

#include "IMUData.h"

class TimeStampedIMUData : public IMUData
{
  private:
 
    unsigned long timestamp;
    
  public:
    TimeStampedIMUData(XYZData acceleration, XYZData gyroscope, XYZData magnetisme)
};

#endif
