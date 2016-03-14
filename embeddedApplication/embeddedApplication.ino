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


#define S_PIN 8
ConcretBeeperController bip = ConcretBeeperController(S_PIN);

File myFile;
FillStorageService *fillStorage;

//IMUData imuData;
float altitudeMax = 0;
float altitude;

int compteur = 0;
    
XYZIMU imu = XYZIMU();
XYZData *acceleration = new XYZData();
XYZData *gyro = new XYZData();
XYZData *magnetic = new XYZData();
IMUData data(acceleration, gyro, magnetic,0.0f);


void setup() {
  Serial.begin(9600);
  /**************************************************************/
  /************************** Les capteurs **********************/
  /**************************************************************/
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
  
  /**************************************************************/
  /***************** Le fichier de sauvgarde*********************/
  /**************************************************************/
  pinMode(SS, OUTPUT);
  
  if (!SD.begin(4)) {//pin 4 
    Serial.println("initialization failed!");
    return; // a changer pour un song disant que ce n'est pas pret à enregistrer (erreur)
  }
  Serial.println("initialization done.");
  // a changer pour le song pret à enregistrer (en bas)
  
  if (SD.exists("test.txt")){ 
    Serial.println("example.txt exists.");
    Serial.println("Removing example.txt...");
    SD.remove("test.txt");
  }
  else {
    Serial.println("example.txt doesn't exist.");  
  }
  
  myFile = SD.open("test.txt", FILE_WRITE);
  
  if (myFile) {
    Serial.println("test : ");
    //myFile.println("Values:");
  } else {
    // a changer pour un song disant que ce n'est pas pret à enregistrer (erreur)
  }
  
  fillStorage = new FillStorageService(myFile);
  
  /**************************************************************/
  /************************** Le beepeur   **********************/
  /**************************************************************/
  bip.errorRing();
    
}

void loop() {
  
  // Insert les nouvelles valeurs 
  imu.getAccelerationData(acceleration);
  imu.getGyroscopeData(gyro);
  imu.getMagnetismData(magnetic);
  altitude = imu.getBarometerData();

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

  
  /************************* Parachute *************************/
  
//  if(pressure < pressureMax)
//  {
//    pressureMax = pressure;
//  }
//  else
//  {
//    deployeParachute();
//  }
  /************************* End Parachute *************************/
  
  
  /************************* Ring *************************/
//  if (pressure = PressureMax)
//  {
//    bip.ring();
//  }
  /************************* End Ring *************************/
  
  /************************* Save Data *************************/

 fillStorage->saveData(data.toChar());

  /************************* End Save Data *************************/
  
  
  /************************* Send Data *****************************/
//  sendData(row)
  /************************* End Send Data *************************/
  compteur = compteur +1;
  if(compteur == 10)
  {
    myFile.close();
    Serial.println("fin");
  }

}

