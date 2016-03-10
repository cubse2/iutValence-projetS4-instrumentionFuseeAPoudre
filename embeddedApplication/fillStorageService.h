#ifndef FILLSTORAGESERVICE_H
#define FILLSTORAGESERVICE_H

#include "StorageService.h"

class FillStorageService : public StorageSercice
{
	public:
		bool saveData(char* data);
		FillStorageService(File file);
};

#endif
