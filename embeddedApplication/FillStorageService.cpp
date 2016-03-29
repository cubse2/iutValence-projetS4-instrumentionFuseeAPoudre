#include "FillStorageService.h"

FillStorageService::FillStorageService(File file)
{
	this->myFile = file;
};

void FillStorageService::saveData(char* data)
{
  myFile.println(data);
};

