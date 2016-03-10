#ifndef FILLSTORAGESERVICE_H
#define FILLSTORAGESERVICE_H

#include "StorageService.h"
#include <SPI.h>
#include <SD.h>

class FillStorageService : public StorageService
{
	private:
		File myFile;
	public:
		bool saveData(char* data);
		FillStorageService(File file);
};

#endif
