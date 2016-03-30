#ifndef CONCRETBEEPERCONTROLLER_H
#define CONCRETBEEPERCONTROLLER_H

#include "SpeakerController.h"

class ConcretSpeakerController : public SpeakerController
{
  private:
	  int speakerPin;
  public:
  	ConcretSpeakerController(int speakerPin);
    void ring(int note, int noteDuration);
    void ringOfStart();
    void ringOfEnd(); 
    void errorOfSDCardRing();
    void errorOfSensorRing();
    void errorOfConst();
};

#endif
