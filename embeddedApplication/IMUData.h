#include "XYZData.h"

#ifndef IMUData_h
#define IMUData_h


class IMUData
{
  private:
  
    float accelerationX;
    float accelerationY;
    float accelerationZ;
    float gyroscopeX;
    float gyroscopeY;
    float gyroscopeZ;
    float magnetismX;
    float magnetismY;
    float magnetismZ;
    float pressure;
    
  public:
    IMUData(XYZData acceleration, XYZData gyroscope, 
      XYZData magnetism, float pressure);
};

#endif
