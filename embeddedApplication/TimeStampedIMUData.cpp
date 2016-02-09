#include "TimeStampedIMUData.h"

TimeStampedIMUData::TimeStampedIMUData(XYZData acceleration, XYZData gyroscope,
		XYZData magnetisme, float pressure, unsigned long time) :
		IMUData(acceleration, gyroscope, magnetisme, pressure)
{
	this->timestamp = time;
}

char* TimeStampedIMUData::toChar()
{
	char timeStampedIMUData[78];
	char timeChar[6];	// TODO : to check !!!

	sprintf(timeChar, "%f;", timestamp); //TODO : link with IMUData, more short?

	strcpy(timeStampedIMUData, acceleration.toChar());
	strcat(timeStampedIMUData, gyroscope.toChar());
	strcat(timeStampedIMUData, magnetism.toChar());
	strcat(timeChar, timeStampedIMUData);

	return timeStampedIMUData;
};
