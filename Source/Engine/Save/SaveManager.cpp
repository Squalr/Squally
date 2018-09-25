#include "SaveManager.h"

const std::string SaveManager::globalSaveFileName = "Global.sav";
const std::string SaveManager::profileSaveFileTemplate = "SaveGame_%d.sav";

SaveManager* SaveManager::instance = nullptr;

SaveManager::SaveManager()
{
}

SaveManager::~SaveManager()
{
}

SaveManager* SaveManager::getInstance()
{
	if (SaveManager::instance == nullptr)
	{
		SaveManager::instance = new SaveManager();
		SaveManager::instance->initialize();
	}

	return SaveManager::instance;
}

void SaveManager::initialize()
{
	SaveManager::setActiveSaveProfile(0);

	if (FileUtils::getInstance()->isFileExist(SaveManager::instance->getGlobalSaveFileName()))
	{
		SaveManager::instance->globalSaveData = FileUtils::getInstance()->deserializeValueMapFromFile(SaveManager::instance->getGlobalSaveFileName());
	}
	else
	{
		SaveManager::instance->globalSaveData = ValueMap();
	}
}

void SaveManager::setActiveSaveProfile(ActiveSaveProfile activeSaveProfile)
{
	SaveManager* instance = SaveManager::getInstance();

	if (FileUtils::getInstance()->isFileExist(instance->getActiveProfileSaveFileName()))
	{
		instance->profileSaveData = FileUtils::getInstance()->deserializeValueMapFromFile(instance->getGlobalSaveFileName());
	}
	else
	{
		instance->profileSaveData = ValueMap();
	}
}

void SaveManager::saveGlobalData(std::string key, cocos2d::Value data)
{
	SaveManager* instance = SaveManager::getInstance();

	instance->globalSaveData.emplace(key, data);

	FileUtils::getInstance()->writeValueMapToFile(instance->globalSaveData, instance->getGlobalSaveFileName());
}

void SaveManager::saveProfileData(std::string key, cocos2d::Value data)
{
	SaveManager* instance = SaveManager::getInstance();

	instance->profileSaveData.emplace(key, data);

	FileUtils::getInstance()->writeValueMapToFile(instance->profileSaveData, instance->getActiveProfileSaveFileName());
}

cocos2d::Value SaveManager::getGlobalData(std::string key)
{
	SaveManager* instance = SaveManager::getInstance();

	if (!GameUtils::keyExists(&instance->globalSaveData, key))
	{
		return cocos2d::Value();
	}
	else
	{
		return instance->globalSaveData.at(key);
	}
}

cocos2d::Value SaveManager::getProfileData(std::string key)
{
	SaveManager* instance = SaveManager::getInstance();

	if (!GameUtils::keyExists(&instance->profileSaveData, key))
	{
		return cocos2d::Value();
	}
	else
	{
		return instance->profileSaveData.at(key);
	}
}

bool SaveManager::hasGlobalData(std::string key)
{
	SaveManager* instance = SaveManager::getInstance();

	return GameUtils::keyExists(&instance->globalSaveData, key);
}

bool SaveManager::hasProfileData(std::string key)
{
	SaveManager* instance = SaveManager::getInstance();

	return GameUtils::keyExists(&instance->profileSaveData, key);
}

std::string SaveManager::getGlobalSaveFileName()
{
	std::string path = (FileUtils::sharedFileUtils()->getWritablePath() + "/").c_str();

	return path + SaveManager::globalSaveFileName;
}

std::string SaveManager::getActiveProfileSaveFileName()
{
	std::string path = (FileUtils::sharedFileUtils()->getWritablePath() + "/").c_str();
	std::string fileName = StrUtils::replaceAll(SaveManager::profileSaveFileTemplate.c_str(), "%d", std::to_string(SaveManager::getActiveSaveProfile()));
	
	return path + fileName;
}

SaveManager::ActiveSaveProfile SaveManager::getActiveSaveProfile()
{
	return SaveManager::getInstance()->activeSaveProfile;
}
