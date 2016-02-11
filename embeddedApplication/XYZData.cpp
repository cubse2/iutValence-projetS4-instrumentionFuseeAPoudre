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

char* XYZData::toChar() const
{
  char xyzData[24];
  sprintf(xyzData, "%.3f;%.3f;%.3f;", x,y,z);
  return xyzData;
}
