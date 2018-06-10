#include "SaveManager.h"

const std::string SaveManager::saveFileName = "SaveGame_%d.sav";

SaveManager* SaveManager::saveManagerInstance = nullptr;

SaveManager::SaveManager()
{
	SaveManager::setActiveSave(0);
}

SaveManager::~SaveManager()
{
}

SaveManager* SaveManager::getInstance()
{
	if (SaveManager::saveManagerInstance == nullptr)
	{
		SaveManager::saveManagerInstance = new SaveManager();
	}

	return SaveManager::saveManagerInstance;
}

ValueMap* SaveManager::getValueMap()
{
	SaveManager* instance = SaveManager::getInstance();

	return &instance->saveData;
}

void SaveManager::setActiveSave(int index)
{
	SaveManager* instance = SaveManager::getInstance();

	instance->saveFile = (FileUtils::sharedFileUtils()->getWritablePath() + "\\").c_str() + printf_s(SaveManager::saveFileName.c_str(), index);
	instance->saveData = FileUtils::getInstance()->deserializeValueMapFromFile(instance->saveFile);
}

void SaveManager::save()
{
	SaveManager* instance = SaveManager::getInstance();

	FileUtils::getInstance()->writeValueMapToFile(instance->saveData, instance->saveFile);
}
