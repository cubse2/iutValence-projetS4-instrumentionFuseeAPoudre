#ifndef SERVOPARACHUTECONTROLLER_H
#define SERVOPARACHUTECONTROLLER_H
#define XBEEPIN 9

#include <Servo.h>
#include "ParachuteController.h"

class ServoParachuteController : public ParachuteController
 {
   private:
     int servoPin
     
    public:
      ServoParachuteController(int servoPin);
      void deploy();  
 };

#endif

