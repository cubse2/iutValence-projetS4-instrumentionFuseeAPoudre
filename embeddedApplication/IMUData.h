#ifndef IMUDATA_H
#define IMUDATA_H

#include "XYZData.h"


class IMUData
{
  private:
 
    float pressure;
    XYZData *acceleration;
    XYZData *gyroscope;
    XYZData *magnetism;
    
  public:
    IMUData(XYZData *acceleration, XYZData *gyroscope, 
      XYZData *magnetism, float pressure);
    void setAcceleration(XYZData *accelerationData);
    void setGyroscope(XYZData *gyroscopeData);
    void setMagnetism(XYZData *magnetismData);
    void setPressure(float pressureData);
    void setIMUData(XYZData *accelerationData, XYZData *gyroscopeData,
          XYZData *magnetismData, float pressureData);
    char* toChar() const;
};

#endif

