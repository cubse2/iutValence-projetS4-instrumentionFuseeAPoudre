#include "TimeStampedIMUData.h"

TimeStampedIMUData::TimeStampedIMUData(unsigned long theTime, XYZData *acceleration, XYZData *gyroscope,
		XYZData *magnetisme, float altitude) :
		IMUData(acceleration, gyroscope, magnetisme, altitude)
{
	this->timestamp = theTime;
}

void TimeStampedIMUData::setTimestamp(unsigned long theTime)
{
  this->timestamp = theTime;
}

void TimeStampedIMUData::setTimeStampedIMUData(unsigned long theTime, XYZData *accelerationData, XYZData *gyroscopeData, 
      XYZData *magnetismData, float altitude)
{
  setTimestamp(theTime);
  setAcceleration(accelerationData);
  setGyroscope(gyroscopeData);
  setMagnetism(magnetismData);
  setAltitude(altitude);
}

char* TimeStampedIMUData::toChar()
{
  char timeStampedIMUData[150];
  char timeData[20];
  dtostrf(timestamp, 10, 0, timeData);
  char altitudeData[10];
  dtostrf(altitude, 4, 2, altitudeData);

  strcpy(timeStampedIMUData, timeData);
  strcat(timeStampedIMUData, ";");
  strcat(timeStampedIMUData, acceleration->toChar());
  strcat(timeStampedIMUData, gyroscope->toChar());
  strcat(timeStampedIMUData, magnetism->toChar());
  strcat(timeStampedIMUData, altitudeData);
  
  return timeStampedIMUData;
}
