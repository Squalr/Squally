#include "SaveManager.h"

#include "cocos/base/CCValue.h"
#include "cocos/platform/CCFileUtils.h"

#include "steam_api.h"

#include "Engine/Steam/Steam.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

const std::string SaveManager::globalSaveFileName = "Global.sqa";
const std::string SaveManager::profileSaveFileTemplate = "SaveGame_%d.sqa";
const std::string SaveManager::SaveKeyIncrement = "SAVE_KEY_INCREMENT";

SaveManager::ActiveSaveProfile SaveManager::activeSaveProfile = ActiveSaveProfile(0);
ValueMap SaveManager::globalSaveData = ValueMap();
ValueMap SaveManager::profileSaveData = ValueMap();
std::map<std::string, cocos2d::ValueMap> SaveManager::saveFileCache = std::map<std::string, cocos2d::ValueMap>();

void SaveManager::initializeSaveData()
{
	static bool initialized = false;

	if (!initialized)
	{
		initialized = true;

		setActiveSaveProfile(0);

		// Load global save data (all data independent of individual profiles)
		SaveManager::globalSaveData = SaveManager::loadSaveFile(
			SaveManager::getLocalGlobalSaveFilePath(),
			SaveManager::getCloudGlobalSaveFilePath()
		);
	}
}

void SaveManager::setActiveSaveProfile(ActiveSaveProfile activeSaveProfile)
{
	SaveManager::activeSaveProfile = activeSaveProfile;

	// Load the save data for this profile
	SaveManager::profileSaveData = SaveManager::loadSaveFile(
		SaveManager::getLocalProfileSaveFilePath(SaveManager::getActiveSaveProfile()),
		SaveManager::getCloudProfileSaveFilePath(SaveManager::getActiveSaveProfile())
	);
}

void SaveManager::saveGlobalData(std::string key, const Value& data)
{
	SaveManager::initializeSaveData();

	SaveManager::globalSaveData[key] = data;

	SaveManager::doSave(SaveManager::globalSaveData, SaveManager::getLocalGlobalSaveFilePath(), SaveManager::getCloudGlobalSaveFilePath());
}

void SaveManager::batchSaveGlobalData(std::vector<std::tuple<std::string, const cocos2d::Value&>> newData)
{
	SaveManager::initializeSaveData();

	for (auto it = newData.begin(); it != newData.end(); it++)
	{
		SaveManager::profileSaveData[std::get<0>(*it)] = std::get<1>(*it);
	}

	SaveManager::doSave(SaveManager::globalSaveData, SaveManager::getLocalGlobalSaveFilePath(), SaveManager::getCloudGlobalSaveFilePath());
}

void SaveManager::batchSaveProfileData(std::vector<std::tuple<std::string, const cocos2d::Value&>> newData)
{
	SaveManager::initializeSaveData();

	for (auto it = newData.begin(); it != newData.end(); it++)
	{
		SaveManager::profileSaveData[std::get<0>(*it)] = std::get<1>(*it);
	}

	SaveManager::doSave(
		SaveManager::profileSaveData,
		SaveManager::getLocalProfileSaveFilePath(SaveManager::getActiveSaveProfile()),
		SaveManager::getCloudProfileSaveFilePath(SaveManager::getActiveSaveProfile())
	);
}

void SaveManager::softSaveProfileData(std::string key, const Value& data)
{
	SaveManager::initializeSaveData();

	SaveManager::profileSaveData[key] = data;
}

void SaveManager::saveProfileData(std::string key, const Value& data)
{
	SaveManager::initializeSaveData();

	SaveManager::profileSaveData[key] = data;

	SaveManager::doSave(
		SaveManager::profileSaveData,
		SaveManager::getLocalProfileSaveFilePath(SaveManager::getActiveSaveProfile()),
		SaveManager::getCloudProfileSaveFilePath(SaveManager::getActiveSaveProfile())
	);
}

Value SaveManager::getGlobalDataOrDefault(std::string key, const Value& defaultValue)
{
	SaveManager::initializeSaveData();

	return GameUtils::getKeyOrDefault(SaveManager::globalSaveData, key, defaultValue);
}

Value SaveManager::getGlobalData(std::string key)
{
	SaveManager::initializeSaveData();

	return GameUtils::getKeyOrDefault(SaveManager::globalSaveData, key, Value());
}

Value SaveManager::getProfileDataOrDefault(std::string key, const Value& defaultValue)
{
	SaveManager::initializeSaveData();

	return GameUtils::getKeyOrDefault(SaveManager::profileSaveData, key, defaultValue);
}

Value SaveManager::getProfileData(std::string key)
{
	SaveManager::initializeSaveData();

	return GameUtils::getKeyOrDefault(SaveManager::profileSaveData, key, Value());
}

SaveManager::ActiveSaveProfile SaveManager::getActiveSaveProfile()
{
	return SaveManager::activeSaveProfile;
}

void SaveManager::doSave(ValueMap valueMap, std::string localSavePath, std::string cloudSavePath)
{
	// Increment save counter
	valueMap[SaveManager::SaveKeyIncrement] = GameUtils::getKeyOrDefault(valueMap, SaveManager::SaveKeyIncrement, Value(0)).asUnsignedInt() + 1;

	// Update saves in cache
	SaveManager::saveFileCache[localSavePath] = valueMap;
	SaveManager::saveFileCache[cloudSavePath] = valueMap;

	// Save to cloud if available
	if (Steam::isCloudSaveAvailable())
	{
		ISteamRemoteStorage* steamRemoteStorage = SteamRemoteStorage();
		const char* file = cloudSavePath.c_str();

		std::stringstream result;
		
		try
		{
			if (FileUtils::getInstance()->serializeValueMapToStream(valueMap, result))
			{
				std::string resultData = result.str();
				bool writeSuccess = steamRemoteStorage->FileWrite(file, resultData.c_str(), resultData.size());

				if (!writeSuccess)
				{
					LogUtils::logError("Error writing cloud save file: " + cloudSavePath);
				}
			}
		}
		catch (const std::exception& ex)
		{
			LogUtils::logError(ex.what());
		}
		catch (const std::string& ex)
		{
			LogUtils::logError(ex);
		}
		catch (...)
		{
			LogUtils::logError("Unknown cloud save file write error on file: " + cloudSavePath);
		}
	}

	// Always write locally as well
	try
	{
		bool writeSuccess = FileUtils::getInstance()->serializeValueMapToFile(valueMap, localSavePath);

		if (!writeSuccess)
		{
			LogUtils::logError("Error writing local save file: " + localSavePath);
		}
	}
	catch (const std::exception& ex)
	{
		LogUtils::logError(ex.what());
	}
	catch (const std::string& ex)
	{
		LogUtils::logError(ex);
	}
	catch (...)
	{
		LogUtils::logError("Unknown local save file write error on file: " + localSavePath);
	}
}

ValueMap SaveManager::loadSaveFile(std::string localSavePath, std::string cloudSavePath)
{
	ValueMap cloudValueMap = ValueMap();
	ValueMap localValueMap = ValueMap();
	
	if (SaveManager::saveFileCache.find(cloudSavePath) == SaveManager::saveFileCache.end())
	{
		bool cloudReadSuccess = false;

		// Load from cloud if it's available
		if (Steam::isCloudSaveAvailable())
		{
			ISteamRemoteStorage* steamRemoteStorage = SteamRemoteStorage();
			const char* file = cloudSavePath.c_str();

			if (steamRemoteStorage->FileExists(file))
			{
				int fileSize = steamRemoteStorage->GetFileSize(file);
				std::unique_ptr<char> result(new char[fileSize]);
				int bytesRead = steamRemoteStorage->FileRead(file, (void*)result.get(), fileSize);

				if (bytesRead == fileSize)
				{
					try
					{
						cloudValueMap = FileUtils::getInstance()->deserializeValueMapFromData(result.get(), fileSize);
						cloudReadSuccess = true;
					}
					catch (const std::exception& ex)
					{
						LogUtils::logError(ex.what());
					}
					catch (const std::string& ex)
					{
						LogUtils::logError(ex);
					}
					catch (...)
					{
						LogUtils::logError("Unknown cloud save file read error on file: " + localSavePath);
					}
				}
			}
		}
	}
	else
	{
		cloudValueMap = SaveManager::saveFileCache[cloudSavePath];
	}

	if (SaveManager::saveFileCache.find(localSavePath) == SaveManager::saveFileCache.end())
	{
		// Access local storage if steam is not available, the file does not exist in the cloud, or the cloud read failed
		try
		{
			if (FileUtils::getInstance()->isFileExist(localSavePath))
			{
				localValueMap = FileUtils::getInstance()->deserializeValueMapFromFile(localSavePath);
			}
		}
		catch (const std::exception& ex)
		{
			LogUtils::logError(ex.what());
		}
		catch (const std::string& ex)
		{
			LogUtils::logError(ex);
		}
		catch (...)
		{
			LogUtils::logError("Unknown local save file read error on file: " + localSavePath);
		}
	}
	else
	{
		localValueMap =	SaveManager::saveFileCache[localSavePath];
	}

	// By default, return the cloud save
	ValueMap returnValueMap = cloudValueMap;

	// Choose local or cloud depending on which has the higher save key increment
	if (GameUtils::keyExists(cloudValueMap, SaveManager::SaveKeyIncrement) && GameUtils::keyExists(localValueMap, SaveManager::SaveKeyIncrement))
	{
		unsigned int cloudIncrement = cloudValueMap.at(SaveManager::SaveKeyIncrement).asUnsignedInt();
		unsigned int localIncrement = localValueMap.at(SaveManager::SaveKeyIncrement).asUnsignedInt();

		// Prefer local over cloud, as this is easier for debugging, testing, and users who want to cheat :)
		if (localIncrement >= cloudIncrement)
		{
			returnValueMap = localValueMap;
		}
	}
	// Increment counts not found -- just use a heuristic based on the number of save key entries
	else if (localValueMap.size() >= cloudValueMap.size())
	{
		returnValueMap = localValueMap;
	}

	// Update cache with the 'winning' save file
	SaveManager::saveFileCache[cloudSavePath] = returnValueMap;
	SaveManager::saveFileCache[localSavePath] = returnValueMap;

	return returnValueMap;
}

bool SaveManager::hasSaveProfile(int profileId)
{
	ValueMap saveData = SaveManager::loadSaveFile(
		SaveManager::getLocalProfileSaveFilePath(profileId),
		SaveManager::getCloudProfileSaveFilePath(profileId)
	);

	// If only the increment key is present, this is effectively an empty savefile
	if (saveData.size() == 1 && GameUtils::keyExists(saveData, SaveManager::SaveKeyIncrement))
	{
		return false;
	}

	return !saveData.empty();
}

void SaveManager::batchDeleteProfileData(std::vector<std::string> keys)
{
	for (auto it = keys.begin(); it != keys.end(); it++)
	{
		SaveManager::profileSaveData.erase(*it);
	}

	SaveManager::doSave(
		SaveManager::profileSaveData,
		SaveManager::getLocalProfileSaveFilePath(SaveManager::getActiveSaveProfile()),
		SaveManager::getCloudProfileSaveFilePath(SaveManager::getActiveSaveProfile())
	);
}

void SaveManager::softDeleteProfileData(std::string key)
{
	SaveManager::profileSaveData.erase(key);
}

void SaveManager::deleteProfileData(std::string key)
{
	SaveManager::profileSaveData.erase(key);

	SaveManager::doSave(
		SaveManager::profileSaveData,
		SaveManager::getLocalProfileSaveFilePath(SaveManager::getActiveSaveProfile()),
		SaveManager::getCloudProfileSaveFilePath(SaveManager::getActiveSaveProfile())
	);
}

void SaveManager::deleteAllProfileData(int profileId)
{
	ValueMap oldSaveData = SaveManager::loadSaveFile(
		SaveManager::getLocalProfileSaveFilePath(profileId),
		SaveManager::getCloudProfileSaveFilePath(profileId)
	);

	ValueMap wipedSave = ValueMap();

	// Copy the save increment from the old save file. Prevents clashing in the case where a save fails to delete on the cloud, but is deleted locally.
	wipedSave[SaveManager::SaveKeyIncrement] = GameUtils::getKeyOrDefault(oldSaveData, SaveManager::SaveKeyIncrement, Value(0));

	// Wipe save on disk
	SaveManager::doSave(
		wipedSave,
		SaveManager::getLocalProfileSaveFilePath(profileId),
		SaveManager::getCloudProfileSaveFilePath(profileId)
	);
}

bool SaveManager::hasGlobalData(std::string key)
{
	return GameUtils::keyExists(SaveManager::globalSaveData, key);
}

bool SaveManager::hasProfileData(std::string key)
{
	return GameUtils::keyExists(SaveManager::profileSaveData, key);
}

std::string SaveManager::getLocalGlobalSaveFilePath()
{
	return FileUtils::getInstance()->getWritablePath() + SaveManager::globalSaveFileName;
}

std::string SaveManager::getLocalProfileSaveFilePath(int profileId)
{
	std::string fileName = StrUtils::replaceAll(SaveManager::profileSaveFileTemplate.c_str(), "%d", std::to_string(profileId));
	std::string fullPath = FileUtils::getInstance()->getWritablePath() + fileName;
	
	return fullPath;
}

std::string SaveManager::getCloudGlobalSaveFilePath()
{
	// Raw filename is actually good enough as a path for cloud
	return SaveManager::globalSaveFileName;
}

std::string SaveManager::getCloudProfileSaveFilePath(int profileId)
{
	std::string fileName = StrUtils::replaceAll(SaveManager::profileSaveFileTemplate.c_str(), "%d", std::to_string(profileId));

	// Raw filename is actually good enough as a path for cloud
	return fileName;
}
