#ifndef CONCRETBEEPERCONTROLLER_H
#define CONCRETBEEPERCONTROLLER_H

#include "BeeperController.h"

class ConcretBeeperController : public BeeperController
{
  private:
	int beeperPin;
  public:
	ConcretBeeperController(int beeperPin);
	void ring();
};

#endif
