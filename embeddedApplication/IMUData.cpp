#include "IMUData.h"


IMUData::IMUData(XYZData *acceleration, XYZData *gyroscope, XYZData *magnetism, float altitude)
{
    this->acceleration = acceleration;
    this->gyroscope = gyroscope;
    this->magnetism = magnetism;
    this->altitude = altitude;
}

void IMUData::setAcceleration(XYZData *accelerationData)
{
  acceleration = accelerationData;
}
void IMUData::setGyroscope(XYZData *gyroscopeData)
{
  this->gyroscope = gyroscopeData;
}
void IMUData::setMagnetism(XYZData *magnetismData)
{
  this->magnetism = magnetismData;
}
void IMUData::setAltitude(float altitudeData)
{
  this->altitude = altitudeData;
}

void IMUData::setIMUData(XYZData *accelerationData, XYZData *gyroscopeData, 
      XYZData *magnetismData, float altitude)
{
  setAcceleration(accelerationData);
  setGyroscope(gyroscopeData);
  setMagnetism(magnetismData);
  setAltitude(altitude);
}

char* IMUData::toChar()
{
	char imuData[150]; 
	char altitudeData[8];
        dtostrf(altitude, 4, 2, altitudeData);

	strcpy(imuData, acceleration->toChar());
	strcat(imuData, gyroscope->toChar());
	strcat(imuData, magnetism->toChar());
	strcat(imuData, altitudeData);

  return imuData;
}

