#include "ServoParachuteController.h"

ServoParachuteController::ServoParachuteController(int servoPin)
{
  this->servoPin = servoPin;
}

void ServoParachuteController::deploy()
{
    myservo.attach(servoPin);  
    int pos = 180;    
    myservo.write(pos);
}

