#include "IMUData.h"


IMUData::IMUData(XYZData *acceleration, XYZData *gyroscope, XYZData *magnetism, float pressure)
{
    this->acceleration = acceleration;
    this->gyroscope = gyroscope;
    this->magnetism = magnetism;
    this->pressure = pressure;
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
void IMUData::setPressure(float pressureData)
{
  this->pressure = pressureData;
}

void IMUData::setIMUData(XYZData *accelerationData, XYZData *gyroscopeData,
      XYZData *magnetismData, float pressureData)
{
  setAcceleration(accelerationData);
  setGyroscope(gyroscopeData);
  setMagnetism(magnetismData);
  setPressure(pressureData);
}

char* IMUData::toChar() const
{
	char imuData[72];
	char pressureChar[7];
	sprintf(pressureChar, "%.3f;", pressure);

	strcpy(imuData, acceleration->toChar());
	strcat(imuData, gyroscope->toChar());
	strcat(imuData, magnetism->toChar());
	strcat(imuData, pressureChar);

  	return imuData;
}
