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
#include "ConcretSpeakerController.h"
#include "TimeStampedIMUData.h"
#include "forUser.h"

//Les variables pour le stockage de donnees
File myFile;
FillStorageService *fillStorage;

//le servomoteur
Servo myServo;

//le beeper
ConcretSpeakerController bip = ConcretSpeakerController(SPEAKER_PIN);

//Booleen pour les etats
bool parachute = false;
bool endRecord = true;

//les float pour les altitudes : actuel / minimum / maximum
float altitudeMin = 0;
float altitudeMax = 0;
float altitudeData = 0;

//le temps
unsigned long theTime = millis();

//objet lie à la recolte des donnees sur la central inertiel
XYZIMU imu = XYZIMU();

//XYZData utilisé pour la moyenne des valeurs
XYZData *recordAcceleration = new XYZData();
XYZData *recordGyroscop = new XYZData();
XYZData *recordMagnetic = new XYZData();

//les XYZData qui forment le TimeStampedIMUData, ou la chaine de caractere a enregistrer
XYZData *accelerationData = new XYZData();
XYZData *gyroscopData = new XYZData();
XYZData *magneticData = new XYZData();

//le timeStampedIMUData 
TimeStampedIMUData data(theTime, accelerationData, gyroscopData, magneticData,0.0f);


void setup() {
  
  Serial.begin(115200);
  /* Verification */

  // Les constants
  checkOfConst();
  
  // Les capteurs
  checkDOF();
  
  // Le fichier de sauvegarde
  checkSDCard();

  // se Speaker et le servomoteur
  bip.ringOfStart();
  myServo.attach(SERVO_PIN);
}

void loop() 
{
  /******************** Détection du décolage *******************/  
  initialization();
  
  //Si on monte
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
    while(1)
    {
      bip.ringOfEnd();
      Serial.println("Fin");
      delay(10000);
    }
  }

}



