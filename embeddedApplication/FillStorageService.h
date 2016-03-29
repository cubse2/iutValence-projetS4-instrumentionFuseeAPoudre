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
		FillStorageService(File file);
                void saveData(char* data);
                void closeFile();
};

#endif
