#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include "FillStorageservice.h" 
#include "XYZIMU.h"
#include "ConcretBeeperController.h"
//#include "IMUData.h"
#include "TimeStampedIMUData.h"


/*Toutes les valeurs sont strictement positif*/
#define SERVO_PIN 9     // pin du servomoteur
#define SPEAKER_PIN 8   // pin du speaker
#define NB_RECORD 5     // nombre d'échantillons pris pour faire une moyenne
#define ROTATION 180    // angle de rotation du servomoteur
#define TIME_BEFORE_DEPLOY 5 // temps avant le déploiment du parachute
#define FALL_DISTANCE 2 // distance de chute minimum après le déploiment du parachute


File myFile;
FillStorageService *fillStorage;
Servo myServo;
ConcretBeeperController bip = ConcretBeeperController(SPEAKER_PIN);

/*Booleen pour les etats*/
bool parachute = false;
bool parachuteOpen = false;
bool endRecord = false;

float altitudeMin = 0;
float altitudeMax = 0;
float altitudeData = 0;
unsigned long theTime = millis();
XYZData *accelerationData = new XYZData();
XYZData *gyroscopData = new XYZData();
XYZData *magneticData = new XYZData();
    
XYZIMU imu = XYZIMU();
XYZData *recordAcceleration = new XYZData();
XYZData *recordGyroscop = new XYZData();
XYZData *recordMagnetic = new XYZData();
//IMUData data(accelerationData, gyroscopData, magneticData,0.0f);
TimeStampedIMUData data(theTime, accelerationData, gyroscopData, magneticData,0.0f);


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
  /********************** Le beepeur et Servo *******************/
  /**************************************************************/
  bip.ring();
  myServo.attach(SERVO_PIN);
}

void loop() {
  
  /******************** Détection du décolage *******************/  
  imu.getAccelerationData(accelerationData);
  imu.getGyroscopeData(gyroscopData);
  imu.getMagnetismData(magneticData);
  altitudeData = imu.getBarometerData();
  Serial.println("-------------------");
  Serial.println(altitudeData);
  
  for(int nbOfRecord = 1; nbOfRecord < 20 ; nbOfRecord++)
  {
    altitudeData = altitudeData + imu.getBarometerData();
  }
  
  altitudeData = altitudeData/20;
  
  if(altitudeMin == 0)
  {
    altitudeMin = altitudeData;
    Serial.println(altitudeMin);
  }
  Serial.println(altitudeData);
  Serial.println("-------------------");
  
  if(altitudeData > altitudeMin + 1)
  {
  /************************ Montée ******************************/  
    rising();
  /************************* Parachute **************************/  
    parachuteActivation();
  /****************** Distance de chute minimum *****************/  
    fall();
  /********************* Fin d'enregistrement *******************/  
    landing();
    
    while(1);
    {
      Serial.println("Fin");
      delay(10000);
    }
  }
  
}

/*********************************************************************************/
/******************************* Les différents états ****************************/
/*********************************************************************************/
/* 1ere etape */
void rising()
{
  Serial.println("1ere");
  while(parachute == false)
  {    
    recording();
     
    if(altitudeData > altitudeMax)
    {
      altitudeMax = altitudeData;
    }
    else 
    if(altitudeMax - altitudeData > 1)
    {
      parachute = true;
    }
  }
}

/* 2eme etape */
void parachuteActivation()
{
  Serial.println("2eme");
  int timeOnTheTop = millis();
  int timeParachute = millis();
  
  while(timeOnTheTop - timeParachute <= TIME_BEFORE_DEPLOY*1000)
  {  
    recording();
    timeOnTheTop = millis();
  }
  myServo.write(ROTATION); // Activation du parachute
}

/* 3eme etape */
void fall()
{
  Serial.println("3eme");
  if(FALL_DISTANCE != 0)
  {
    while(altitudeMax-altitudeData <= FALL_DISTANCE)
    {
      recording();
      Serial.println(altitudeMax-altitudeData);
    }
  }
}

/* 4eme etape */
void landing()
{
  int nbOfRecord = 0;
  int alti = 0;
  Serial.println("4eme");
  while(endRecord == false)
  { 
    recording();
    if (nbOfRecord == 10)
    {
      if(alti+0.1 <= altitudeMin <= alti+0.1)
      {
        Serial.println("close file");
        myFile.close();
        endRecord = true;
      }
    }
    else
    {
      nbOfRecord = nbOfRecord+1;
      alti = alti + altitudeData;
    }
    altitudeMin = altitudeData;
  }
}

/***********************  Echantillonage et Enregistrement des données  ********************/
void recording()
{
  imu.getAccelerationData(accelerationData);
  imu.getGyroscopeData(gyroscopData);
  imu.getMagnetismData(magneticData);
  altitudeData = imu.getBarometerData();
  
  for(int nbOfRecord = 1; nbOfRecord < NB_RECORD; nbOfRecord++)
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
  
  theTime = millis();
  
  //data.setIMUData(accelerationData, gyroscopData, magneticData, altitudeData);
  data.setTimeStampedIMUData(theTime,accelerationData, gyroscopData, magneticData, altitudeData);
  
  //Enregistrement
  fillStorage->saveData(data.toChar());
  
  Serial.println(data.toChar());
}

/***********************  Addition de deux XYZData  ********************/
void addValue(XYZData *data, XYZData *add)
{
  data->setX(data->getX()+add->getX());
  data->setY(data->getY()+add->getY());
  data->setZ(data->getZ()+add->getZ());
}
/***********************  moyenne de XYZData  ********************/
void averageValue(XYZData *data, int average)
{
  data->setX(data->getX()/average);
  data->setY(data->getY()/average);
  data->setZ(data->getZ()/average);
}
