#ifndef IMU_h
#define IMU_h

#include "XYZData.h"
#include "IMUData.h"

class IMU
{
  protected:
    virtual void getAccelerationData(XYZData * data);
    virtual void getMagnetismData(XYZData * data);
    virtual void getGyroscopeData(XYZData * data);
    virtual float getBarometerData();
};

#endif
