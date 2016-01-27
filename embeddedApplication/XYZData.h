#ifndef XYZData_h
#define XYZData_h


class XYZData
{
  private:
    float x;
    float y;
    float z;
   
  public:
    XYZData(float x, float y, float z);
    char* toChar();
};

#endif
