#include "XYZData.h"
#include "IMUData.h"

#ifndef IMU_h
#define IMU_h


class IMU
{
  public:
    virtual XYZData getAccelerationData() = 0;
    virtual XYZData getMagnetismData() = 0;
    virtual XYZData getGyroscopeData() = 0;
    virtual float getBarometerData() = 0;
    virtual IMUData getIMUData() = 0;
};

#endif
