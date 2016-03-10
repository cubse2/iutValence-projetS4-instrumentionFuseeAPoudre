#include "XYZIMU.h"


void XYZIMU::getAccelerationData(XYZData *data)
	{
    accel.getEvent(&event);
    data->setX(event.acceleration.x);
    data->setY(event.acceleration.y);
    data->setZ(event.acceleration.z);
	}
	
void XYZIMU::getMagnetismData(XYZData *data)
	{
   mag.getEvent(&event);	
    data->setX(event.magnetic.x);
    data->setY(event.magnetic.y);
    data->setZ(event.magnetic.z);
	}

void XYZIMU::getGyroscopeData(XYZData *data)
	{
		gyro.getEvent(&event);
    data->setX(event.gyro.x);
    data->setY(event.gyro.y);
    data->setZ(event.gyro.z);
	}

float XYZIMU::getBarometerData()
	{
  bmp.getEvent(&event);
  float temperature;
  bmp.getTemperature(&temperature); 
  return bmp.pressureToAltitude(SENSORS_PRESSURE_SEALEVELHPA, event.pressure, temperature); 
	}

XYZIMU::XYZIMU() : event()
{
  
}

