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
    int pause = noteDuration * 1.30;
    
    tone(beeperPin, song, noteDuration);
    delay(pause);
    noTone(beeperPin);
}

void ConcretBeeperController::errorRing()
{
    int melody[] = {262, 196};
    int noteDurations[] = {2, 1};
    
    for(int note = 0; note < sizeof(melody); note++ )
    {
      int noteDuration = 1000 / noteDurations[note];
      tone(beeperPin, melody[note], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(beeperPin);
    }
}
