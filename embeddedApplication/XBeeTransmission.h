#ifndef XBEETRANSMISSION_H
#define XBEETRANSMISSION_H
#include "TransmissionService.h"
#include <SoftwareSerial.h>
#define DOUT 2
#define DIN 3


class XBeeTransmission : public TransmissionService
{
  public:
  xbee.begin(9600);                 
  Serial.begin(9600);
  SoftwareSerial xbee(DOUT, DIN);
  void sendData(data.toChar);
};

#endif
