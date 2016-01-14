#include "IMUData.h"

IMUData::IMUData(XYZData acceleration, XYZData gyroscope, 
        XYZData magnetism, float a_pressure)
{
    accelerationX = acceleration.getX();
    accelerationY = acceleration.getY();
    accelerationZ = acceleration.getZ();
    gyroscopeX = gyroscope.getX();
    gyroscopeY = gyroscope.getY();
    gyroscopeZ = gyroscope.getZ();
    magnetismX = magnetism.getX();
    magnetismY = magnetism.getY();
    magnetismZ = magnetism.getZ();
    pressure = pressure;  
}
