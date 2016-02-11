#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

#include "XYZIMU.h"
#include "IMUData.h"


float t ;
//IMUData imuData;
float pressureMax = 0;
float pressure;

void setup() {
  Serial.begin(9600);
  XYZData *acceleration = new XYZData();
  XYZData *gyro = new XYZData();
  XYZData *magnetic = new XYZData();
  
  IMUData data(acceleration, gyro, magnetic,0.0f);
  XYZIMU imu = XYZIMU();
}

void loop() {
    //IMUData data;
  //XYZIMU imu = XYZIMU();
  //data = imu.getIMUData();

  //Serial.println(data.toChar());
  
//  pressure = imuData.getBarometerValue()
  // ************************* Parachute ************************* //
  
  if(pressure < pressureMax)
  {
    pressureMax = pressure;
  }
  else
  {
//    deployeParachute();
  }
  // ************************* End Parachute ************************* //
  
  
  // ************************* Ring ************************* //
//  if (pressure = PressureMax)
//  {
//    ring();
//  }
  // ************************* End Ring ************************* //
  
  // ************************* Save Data ************************* //
//  t = getTime();               // millis()
//  imuData = getIMUData();
  char row[90];                  // t+Gx+Gy+Gz+Az+Ay+Az+Mx+My+Mz+B (t+Gyro+Accele+Magnet+Baro)    
  sprintf(row, "%.3f", t);
    
//  for (i = 0; i< sizeof(imuData); i++) 
//  {
//    row = row + ";" + imuData[i].toString();
//  }
  
//  saveData(row);
  // ************************* End Save Data ************************* //
  
  
  // ************************* Send Data ************************* //
//  sendData(row)
  // ************************* End Send Data ************************* //

}
