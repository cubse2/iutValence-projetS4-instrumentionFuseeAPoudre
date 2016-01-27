#include "XYZData.h"
#include "IMUData.h"

#ifndef IMU_h
#define IMU_h


class IMU
{
  public:
    XYZData getAccelerationData();
    XYZData getMagnetismData();
    XYZData getGyroscopeData();
    float getBarometerData();
    IMUData getIMUData();
};

#endif
