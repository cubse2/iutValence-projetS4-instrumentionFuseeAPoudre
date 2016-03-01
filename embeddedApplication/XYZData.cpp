#include "XYZData.h"
#include "stdio.h"

XYZData::XYZData()
{
  this->x = 0.0;
  this->y = 0.0;
  this->z = 0.0;
}


XYZData::XYZData(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void XYZData::setX(float x)
{
    this->x = x;
}

void XYZData::setY(float y)
{
    this->y = y;
}

void XYZData::setZ(float z)
{
    this->z = z;
}

char* XYZData::toChar()
{
  char xyzData[50];
  char xData[15];
  dtostrf(x, 3, 2, xData);
  char yData[15];
  dtostrf(y, 3, 2, yData);
  char zData[15];
  dtostrf(z, 3, 2, zData);
//  Serial.println(x);
//  Serial.println(y);
//  Serial.println(z);

  strcpy(xyzData, xData);
  strcat(xyzData, ";");
  strcat(xyzData, yData);
  strcat(xyzData, ";");
  strcat(xyzData, zData);
  strcat(xyzData, ";");

  return xyzData;
}

