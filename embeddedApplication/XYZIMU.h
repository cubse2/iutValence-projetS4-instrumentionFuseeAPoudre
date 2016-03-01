
#ifndef IMUData_h
#define IMUData_h

#include "IMU.h"
#include "IMUData.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>


class XYZIMU : public IMU
{
  private:
  /* Assign a unique ID to the sensors */

    sensors_event_t event;
    
    
  public:
  Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
  Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
  Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
  Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);
    void getAccelerationData(XYZData * data);
    void getMagnetismData(XYZData * data);
    void getGyroscopeData(XYZData * data);
    float getBarometerData();
    XYZIMU();
};

#endif

