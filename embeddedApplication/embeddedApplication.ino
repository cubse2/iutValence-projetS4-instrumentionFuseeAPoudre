float t ;
IMUData imuData;

void setup() {
  Serial.begin(9600);

}

void loop() {
  
  if (fuseeAuSol()){
    ring();
  }
  
  t = getTime();               // millis()
  imuData = getIMUData();
  char row[90];                  // t+Gx+Gy+Gz+Az+Ay+Az+Mx+My+Mz+B (t+Gyro+Accele+Magnet+Baro)    
  sprintf(row, "%.3f", t);   
  for (i = 0; i<size()) 
  

}
