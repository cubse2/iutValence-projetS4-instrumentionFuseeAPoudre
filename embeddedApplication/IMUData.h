#ifndef IMUData_h
#define IMUData_h


class IMUData
{
  private:
  
    float accelerationX;
    float accelerationY;
    float accelerationZ;
    float gyroscopeX;
    float gyroscopeY;
    float gyroscopeZ;
    float magnetismX;
    float magnetismY;
    float magnetismZ;
    float pressure;
    
  public:
  // XYZData a modifier
    IMUData(XYZData acceleration, XYZData gyroscope, 
        XYZData magnetism, float a_pressure)
}

#endif
