#include "SaveManager.h"

const std::string SaveManager::globalSaveFileName = "Global.sqa";
const std::string SaveManager::profileSaveFileTemplate = "SaveGame_%d.sqa";

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

	// Load global save data (all data independent of individual profiles)
	SaveManager::getInstance()->globalSaveData = SaveManager::loadSaveFile(
		SaveManager::getInstance()->getLocalGlobalSaveFilePath(),
		SaveManager::getInstance()->getCloudGlobalSaveFilePath()
	);
}

void SaveManager::setActiveSaveProfile(ActiveSaveProfile activeSaveProfile)
{
	SaveManager::getInstance()->activeSaveProfile = activeSaveProfile;

	// Load the save data for this profile
	SaveManager::getInstance()->profileSaveData = SaveManager::loadSaveFile(
		SaveManager::getInstance()->getLocalActiveProfileSaveFilePath(),
		SaveManager::getInstance()->getCloudActiveProfileSaveFilePath()
	);
}

void SaveManager::saveGlobalData(std::string key, cocos2d::Value data)
{
	SaveManager* instance = SaveManager::getInstance();

	instance->globalSaveData[key] = data;

	SaveManager::doSave(instance->globalSaveData, instance->getLocalGlobalSaveFilePath(), instance->getCloudGlobalSaveFilePath());
}

void SaveManager::saveProfileData(std::string key, cocos2d::Value data)
{
	SaveManager* instance = SaveManager::getInstance();

	instance->profileSaveData[key] = data;

	SaveManager::doSave(instance->profileSaveData, instance->getLocalActiveProfileSaveFilePath(), instance->getCloudActiveProfileSaveFilePath());
}

cocos2d::Value SaveManager::getGlobalDataOrDefault(std::string key, cocos2d::Value defaultValue)
{
	SaveManager* instance = SaveManager::getInstance();

	if (!GameUtils::keyExists(&instance->globalSaveData, key))
	{
		return defaultValue;
	}
	else
	{
		return instance->globalSaveData.at(key);
	}
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

cocos2d::Value SaveManager::getProfileDataOrDefault(std::string key, cocos2d::Value defaultValue)
{
	SaveManager* instance = SaveManager::getInstance();

	if (!GameUtils::keyExists(&instance->profileSaveData, key))
	{
		return defaultValue;
	}
	else
	{
		return instance->profileSaveData.at(key);
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

SaveManager::ActiveSaveProfile SaveManager::getActiveSaveProfile()
{
	return SaveManager::getInstance()->activeSaveProfile;
}

void SaveManager::doSave(ValueMap valueMap, std::string localSavePath, std::string cloudSavePath)
{
	// Save to cloud if available
	if (Steam::isCloudSaveAvailable())
	{
		ISteamRemoteStorage* steamRemoteStorage = SteamRemoteStorage();
		const char* file = cloudSavePath.c_str();

		std::stringstream result;

		if (FileUtils::getInstance()->serializeValueMapToStream(valueMap, result))
		{
			std::string resultData = result.str();
			bool writeSuccess = steamRemoteStorage->FileWrite(file, resultData.c_str(), resultData.size());
		}
	}

	// Always write locally as well
	FileUtils::getInstance()->serializeValueMapToFile(valueMap, localSavePath);
}

ValueMap SaveManager::loadSaveFile(std::string localSavePath, std::string cloudSavePath)
{
	// Load from cloud if it's available
	if (Steam::isCloudSaveAvailable())
	{
		ISteamRemoteStorage* steamRemoteStorage = SteamRemoteStorage();
		const char* file = cloudSavePath.c_str();

		if (steamRemoteStorage->FileExists(file))
		{
			int fileSize = steamRemoteStorage->GetFileSize(file);
			std::unique_ptr<const char> result(new const char[fileSize]);
			int bytesRead = steamRemoteStorage->FileRead(file, (void*)result.get(), fileSize);

			if (bytesRead == fileSize)
			{
				ValueMap deserializedValueMap = FileUtils::getInstance()->deserializeValueMapFromData(result.get(), fileSize);

				return deserializedValueMap;
			}
		}
	}

	// Access local storage if steam is not available, the file does not exist in the cloud, or the cloud read failed
	if (FileUtils::getInstance()->isFileExist(localSavePath))
	{
		return FileUtils::getInstance()->deserializeValueMapFromFile(localSavePath);
	}

	// Nothing found, return an empty valuemap
	return ValueMap();
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

std::string SaveManager::getLocalGlobalSaveFilePath()
{
	return FileUtils::sharedFileUtils()->getWritablePath() + SaveManager::globalSaveFileName;
}

std::string SaveManager::getLocalActiveProfileSaveFilePath()
{
	std::string fileName = StrUtils::replaceAll(SaveManager::profileSaveFileTemplate.c_str(), "%d", std::to_string(SaveManager::getActiveSaveProfile()));
	
	return FileUtils::sharedFileUtils()->getWritablePath() + fileName;
}

std::string SaveManager::getCloudGlobalSaveFilePath()
{
	// Raw filename is actually good enough as a path for cloud
	return SaveManager::globalSaveFileName;
}

std::string SaveManager::getCloudActiveProfileSaveFilePath()
{
	std::string fileName = StrUtils::replaceAll(SaveManager::profileSaveFileTemplate.c_str(), "%d", std::to_string(SaveManager::getActiveSaveProfile()));

	// Raw filename is actually good enough as a path for cloud
	return fileName;
}
