#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H

#include <Arduino.h>

class StorageService
{
	protected:
		virtual void saveData(char* data);
};

#endif
