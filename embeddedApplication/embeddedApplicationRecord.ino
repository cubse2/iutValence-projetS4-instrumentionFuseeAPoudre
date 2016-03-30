/***********************  Enregistrement des données  ********************/
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
