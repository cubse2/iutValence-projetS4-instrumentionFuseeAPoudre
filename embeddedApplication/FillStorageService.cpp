#include "FillStorageService.h"

FillStorageService::FillStorageService(File file)
{
	this->myFile = file;
};

bool FillStorageService::saveData(char* data)
{
	myFile.println(data);
};
