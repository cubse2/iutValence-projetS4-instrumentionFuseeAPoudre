#include "ConcretBeeperController.h"

ConcretBeeperController::ConcretBeeperController(int beeperPin)
{
	this->beeperPin = beeperPin;
}

void ConcretBeeperController::ring()
{
    int song = 262;
    int noteDurations = 4;
    int noteDuration = 1000 / noteDurations;
    
    tone(beeperPin, song, noteDuration);
    delay(60000);
    noTone(beeperPin);
}
