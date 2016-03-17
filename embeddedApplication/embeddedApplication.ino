#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

#include <SPI.h>
#include <SD.h>
#include "FillStorageservice.h" 
#include "XYZIMU.h"
#include "IMUData.h"
#include "ConcretBeeperController.h"
#include <Servo.h>

#define SERVO_PIN 9
#define SPEAKER_PIN 8
#define NB_RECORD 2
#define ROTATION 180

File myFile;
FillStorageService *fillStorage;
Servo myServo;
ConcretBeeperController bip = ConcretBeeperController(SPEAKER_PIN);

//IMUData imuData;
float altitudeMin = 0;
float altitudeMax = 0;
float altitudeData = 0;
XYZData *accelerationData = new XYZData();
XYZData *gyroscopData = new XYZData();
XYZData *magneticData = new XYZData();
    
XYZIMU imu = XYZIMU();
XYZData *recordAcceleration = new XYZData();
XYZData *recordGyroscop = new XYZData();
XYZData *recordMagnetic = new XYZData();
IMUData data(accelerationData, gyroscopData, magneticData,0.0f);


void setup() {
  
  Serial.begin(115200);
  /**************************************************************/
  /************************** Les capteurs **********************/
  /**************************************************************/
  Serial.println(F("Adafruit 10DOF Tester")); 
  Serial.println("");
  
  /* Initialise the sensors */
  if(!imu.accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    bip.errorOfSensorRing();
  }
  
  if(!imu.mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    bip.errorOfSensorRing();
  }
 
  if(!imu.bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    bip.errorOfSensorRing();
  }
  
  if(!imu.gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
    bip.errorOfSensorRing();
  }
  
  /**************************************************************/
  /***************** Le fichier de sauvgarde*********************/
  /**************************************************************/
  pinMode(SS, OUTPUT);
  
  /*Initialisation de la carte*/
  if (!SD.begin(4)) 
  {
    Serial.println("initialization failed!");
    bip.errorOfSDCardRing();
  }
  Serial.println("initialization done.");
  
  /*Espace memoire*/   // A revoir
  //uint32_t volumesize;
  //volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  //volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  //volumesize *= 512;                         // SD card blocks are always 512 bytes
  
  
  /*Si le fichier existe deja*/
  if (SD.exists("flight.txt"))
  { 
    Serial.println("flight.txt exists.");
    Serial.println("Removing flight.txt...");
    SD.remove("flight.txt");
  }
  else 
  {
    Serial.println("flight.txt doesn't exist.");  
  }
  
  /*Creer le fichier*/
  myFile = SD.open("flight.txt", FILE_WRITE);
  
  /*Debut*/
  if (myFile) {
    Serial.println("Flight Data : ");
    //myFile.println("Values:");
  } 
  else 
  {
    bip.errorOfSDCardRing();
  }
  
  fillStorage = new FillStorageService(myFile);
  
  /**************************************************************/
  /************************** Le beepeur   **********************/
  /**************************************************************/
  bip.ring();
  myServo.attach(SERVO_PIN);

}

void loop() {
  
  imu.getAccelerationData(accelerationData);
  imu.getGyroscopeData(gyroscopData);
  imu.getMagnetismData(magneticData);
  altitudeData = imu.getBarometerData();
  
  if(altitudeMin == 0)
  {
    altitudeMin = trunc(altitudeData);
  }
  
  /************************* Record *************************/
  
  if(altitudeData > altitudeMin + 1)
  {
    Serial.println("OK !!!!!");
    while(1)
    {
      imu.getAccelerationData(accelerationData);
      imu.getGyroscopeData(gyroscopData);
      imu.getMagnetismData(magneticData);
      altitudeData = imu.getBarometerData();
      
      for(int nbOfRecord = 0; nbOfRecord <= NB_RECORD-1; nbOfRecord++)
      {
        imu.getAccelerationData(recordAcceleration);
        imu.getGyroscopeData(recordGyroscop);
        imu.getMagnetismData(recordMagnetic);
        addValue(accelerationData, recordAcceleration);
        addValue(gyroscopData, recordGyroscop);
        addValue(magneticData, recordMagnetic);
        altitudeData = altitudeData + imu.getBarometerData();
      }

      averageValue(accelerationData, NB_RECORD);
      averageValue(gyroscopData, NB_RECORD);
      averageValue(magneticData, NB_RECORD);
      altitudeData = altitudeData / NB_RECORD;
    
      // tout dans le IMUData data
      data.setIMUData(accelerationData, gyroscopData, magneticData, altitudeData);
      Serial.println(data.toChar());
      //Serial.println(altitudeData);
  

  /************************* Parachute *************************/
  
      if(altitudeData > altitudeMax)
      {
        altitudeMax = altitudeData;
      }
      else 
      if(altitudeMax - altitudeData > 1)
      {
        Serial.println("fin !!!!");
        myServo.write(ROTATION);
      }
  /************************* End Parachute *************************/
  
  /************************* Save Data *************************/
  
      fillStorage->saveData(data.toChar());
      

  /************************* End Save Data *************************/
  
  
  /************************* Send Data *****************************/
  //  sendData(row)
  /************************* End Send Data *************************/
  
  /***************  Partie Permettant les tests  *******************/
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
    }
  }
  
}

void addValue(XYZData *data, XYZData *add)
{
  data->setX(data->getX()+add->getX());
  data->setY(data->getY()+add->getY());
  data->setZ(data->getZ()+add->getZ());
}

void averageValue(XYZData *data, int average)
{
  data->setX(data->getX()/average);
  data->setY(data->getY()/average);
  data->setZ(data->getZ()/average);
}
