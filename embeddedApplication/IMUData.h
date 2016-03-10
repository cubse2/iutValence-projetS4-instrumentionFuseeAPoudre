#ifndef IMUDATA_H
#define IMUDATA_H

#include "XYZData.h"

class IMUData
{
  private:
 
    float altitude;
    XYZData *acceleration;
    XYZData *gyroscope;
    XYZData *magnetism;
    
  public:
    IMUData(XYZData *acceleration, XYZData *gyroscope, 
      XYZData *magnetism, float pressure);
    void setAcceleration(XYZData *accelerationData);
    void setGyroscope(XYZData *gyroscopeData);
    void setMagnetism(XYZData *magnetismData);
    void setAltitude(float altitudeData);
    void setIMUData(XYZData *accelerationData, XYZData *gyroscopeData, 
      XYZData *magnetismData, float altitude);
    char* toChar();
};
#endif


