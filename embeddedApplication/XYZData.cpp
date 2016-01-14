#include "XYZData.h"

XYZData::XYZData(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
};

float XYZData::getX()
{
  return x;
};

float XYZData::getY()
{
  return y;
};

float XYZData::getZ()
{
  return z;
};
