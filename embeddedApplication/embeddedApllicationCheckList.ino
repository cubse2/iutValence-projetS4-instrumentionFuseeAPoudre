// Verifie si toutes les valeurs du l'utilisateurs sont bien superieur ou egal a 0
void checkOfConst()
{
  if (SERVO_PIN <= 0 || SPEAKER_PIN <= 0)
  {  
    void errorOfConst();
  }

  if (0 > NB_RECORD || NB_RECORD > 10)
  {  
    void errorOfConst();
  }

  if (0 > ROTATION)
  {  
    void errorOfConst();
  }

  if (TIME_BEFORE_DEPLOY < 0 || TIME_BEFORE_DEPLOY > 25)
  {  
    void errorOfConst();
  }

  if (FALL_DISTANCE < 0)
  {
    void errorOfConst();
  }
}

/* Verifie si les capteurs fonctionnent */
void checkDOF()
{
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
}

/* Verifie si la card SD est fonctionnelle */
void checkSDCard()
{
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
}

