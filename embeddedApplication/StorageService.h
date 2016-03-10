#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H

#include <Arduino.h>

class StorageService
{
	protected:
		virtual bool saveData(char* data);
};

#endif
