/*********************************************************************************/
/******************************* Les différents états ****************************/
/*********************************************************************************/
/* Initialisation, ou la partie detection de mouvement*/
void initialization()
{
  int toRing = 0;
  Serial.println("init");
  imu.getAccelerationData(accelerationData);
  imu.getGyroscopeData(gyroscopData);
  imu.getMagnetismData(magneticData);
  altitudeData = imu.getBarometerData();

  // Moyenne de 20 valeurs pour bien detecter le decolage sans trop retarder le temps de calcule de la machine
  for(int nbOfRecord = 1; nbOfRecord < 20 ; nbOfRecord++)
  {
    altitudeData = altitudeData + imu.getBarometerData();
  }
  
  altitudeData = altitudeData/20;

  // altitudeMin prend la toute premiere valeur recolte par altitudeData
  if(altitudeMin == 0)
  {
    altitudeMin = altitudeData;
  }
  if(toRing == 10)
  {
    bip.ringOfStart();
    toRing = 0;
  }
  else
  {
    toRing++;
  }
}

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
  while(endRecord)
  { 
    recording();
    if (nbOfRecord == 10)
    {
      if(alti+0.1 <= altitudeMin <= alti+0.1)
      {
        Serial.println("close file");
        myFile.close();
        endRecord = false;
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

