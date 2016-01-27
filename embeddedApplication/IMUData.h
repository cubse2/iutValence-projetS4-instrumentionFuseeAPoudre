#ifndef IMUData_h
#define IMUData_h

#include "XYZData.h"

class IMUData
{
  private:
 
    float pressure;
    XYZData acceleration;
    XYZData gyroscope;
    XYZData magnetism;
    
  public:
    IMUData(XYZData acceleration, XYZData gyroscope, 
      XYZData magnetism, float pressure);
    char* toChar() const;
};

#endif
