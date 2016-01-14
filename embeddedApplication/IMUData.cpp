#include "IMUData.h"

IMUData::IMUData(XYZData acceleration, XYZData gyroscope, 
        XYZData magnetism, float pressure)
{
    this->accelerationX = acceleration.getX();
    this->accelerationY = acceleration.getY();
    this->accelerationZ = acceleration.getZ();
    this->gyroscopeX = gyroscope.getX();
    this->gyroscopeY = gyroscope.getY();
    this->gyroscopeZ = gyroscope.getZ();
    this->magnetismX = magnetism.getX();
    this->magnetismY = magnetism.getY();
    this->magnetismZ = magnetism.getZ();
    this->pressure = pressure;  
}
