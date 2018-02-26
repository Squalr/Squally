#include "SaveManager.h"

const std::string SaveManager::musicVolumeKey = "music";

SaveManager* SaveManager::configManagerInstance = nullptr;

SaveManager* SaveManager::getInstance()
{
	if (SaveManager::configManagerInstance == nullptr)
	{
		SaveManager::configManagerInstance = new SaveManager();
	}

	return SaveManager::configManagerInstance;
}

SaveManager::SaveManager()
{
	this->saveData = new ValueMap();

	SaveManager::setActiveSave(0);
}

SaveManager::~SaveManager()
{
	delete(this->saveData);
}

void SaveManager::setActiveSave(int index)
{
	SaveManager* instance = SaveManager::getInstance();

	// if (instance->saveData != nullptr)
	{
		// delete(instance->saveData);
	}

	instance->saveFile = printf_s("SaveGame_%d.sav", index);
	// instance->saveData = binn_object();

	// TODO: load from save data
}
