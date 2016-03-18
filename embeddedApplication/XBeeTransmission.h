#ifndef XBEETRANSMISSION_H
#define XBEETRANSMISSION_H

#include "TransmissionService.h"

#define DOUT 2
#define DIN 3


class XBeeTransmission : public TransmissionService
{
  public:
  void sendData();
};

#endif
