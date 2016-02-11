#ifndef XYZDATA_H
#define XYZDATA_H

#include <Arduino.h>

class XYZData
{
  private:
    float x;
    float y;
    float z;
   
  public:
    XYZData();
    XYZData(float x, float y, float z);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    char* toChar() const;
};

#endif
