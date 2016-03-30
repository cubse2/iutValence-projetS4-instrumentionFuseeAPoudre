#ifndef BEEPERCONTROLLER_H
#define BEEPERCONTROLLER_H

#include <Arduino.h>

class SpeakerController
{
  protected:
	virtual void ring(int note, int noteDuration);
};

#endif
