#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

#include "XYZIMU.h"
#include "IMUData.h"
#include "ConcretBeeperController.h"

#define S_PIN 8

ConcretBeeperController bip = ConcretBeeperController(S_PIN);

//IMUData imuData;
float altitudeMax = 0;
float altitude;
    
XYZIMU imu = XYZIMU();
XYZData *acceleration = new XYZData();
XYZData *gyro = new XYZData();
XYZData *magnetic = new XYZData();
IMUData data(acceleration, gyro, magnetic,0.0f);

void setup() {
  Serial.begin(9600);
  Serial.println("test"); 

  Serial.println(F("Adafruit 10DOF Tester")); Serial.println("");
  /* Initialise the sensors */
  if(!imu.accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!imu.mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  if(!imu.bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  if(!imu.gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  // BEEPER
  bip.ring();
}

void loop() {
  
  // Insert les nouvelles valeurs 
  imu.getAccelerationData(acceleration);
  imu.getGyroscopeData(gyro);
  imu.getMagnetismData(magnetic);
  altitude = imu.getBarometerData(); //4.2

  // tout dans le IMUData data
  data.setIMUData(acceleration, gyro, magnetic, altitude);
  Serial.println(data.toChar());
  delay(1000);



//  Partie Permettant les tests
//  Serial.println("Chaque XYZData");
//  Serial.println(acceleration->toChar());
//  Serial.println(gyro->toChar());
//  Serial.println(magnetic->toChar());
//  Serial.println("");
//  Serial.println("la pression");
//  Serial.println(pressure);
//  char pressureData[8];
//  dtostrf(pressure, 4, 2, pressureData);
//  Serial.println(pressureData);
//
//  Serial.println("");
//  Serial.println("Affiche tout");
//  Serial.println(data.toChar());
//  
//  Serial.println("fin");

  
  // ************************* Parachute ************************* //
  
//  if(pressure < pressureMax)
//  {
//    pressureMax = pressure;
//  }
//  else
//  {
//    deployeParachute();
//  }
  // ************************* End Parachute ************************* //
  
  
  // ************************* Ring ************************* //
//  if (pressure = PressureMax)
//  {
//    bip.ring();
//  }
  // ************************* End Ring ************************* //
  
  // ************************* Save Data ************************* //
//  t = getTime();               // millis()
//  imuData = getIMUData();
//  char row[90];                  // t+Gx+Gy+Gz+Az+Ay+Az+Mx+My+Mz+B (t+Gyro+Accele+Magnet+Baro)    
//  sprintf(row, "%.3f", t);
    
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

