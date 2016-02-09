#include "IMUData.h"


IMUData::IMUData(XYZData *acceleration, XYZData *gyroscope, XYZData *magnetism, float pressure)
{
    this->acceleration = acceleration;
    this->gyroscope = gyroscope;
    this->magnetism = magnetism;
    this->pressure = pressure;
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
