#include "XYZData.h"
#include "stdio.h"

XYZData::XYZData(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
};

char* XYZData::toChar()
{
  char xyzData[24];
  sprintf(xyzData, "%.3f;%.3f;%.3f;", x,y,z);
  return xyzData;
};
