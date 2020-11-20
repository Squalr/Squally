#include "SaveManager.h"

#include "cocos/base/CCValue.h"
#include "cocos/platform/CCFileUtils.h"

#include "steam_api.h"

#include "Engine/Steam/Steam.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

const std::string SaveManager::GlobalSaveFileName = "Global.sqa";
const std::string SaveManager::ProfileSaveFileTemplate = "Profile_%d.sqa";
const std::string SaveManager::SaveKeyIncrement = "SAVE_KEY_INCREMENT";

SaveManager::SaveProfile SaveManager::ActiveSaveProfile = SaveProfile(0);
ValueMap SaveManager::GlobalSaveData = ValueMap();
ValueMap SaveManager::ProfileSaveData = ValueMap();
std::map<std::string, cocos2d::ValueMap> SaveManager::SaveFileCache = std::map<std::string, cocos2d::ValueMap>();

bool SaveManager::HasUnsavedChanges = false;

void SaveManager::InitializeSaveData()
{
	static bool initialized = false;

	if (!initialized)
	{
		initialized = true;

		SetActiveSaveProfile(0);

		// Load global save data (all data independent of individual profiles)
		SaveManager::GlobalSaveData = SaveManager::LoadSaveFile(
			SaveManager::GetLocalGlobalSaveFilePath(),
			SaveManager::GetCloudGlobalSaveFilePath()
		);
	}
}

void SaveManager::SetActiveSaveProfile(SaveProfile ActiveSaveProfile)
{
	SaveManager::InitializeSaveData();

	SaveManager::ActiveSaveProfile = ActiveSaveProfile;

	// Load the save data for this profile
	SaveManager::ProfileSaveData = SaveManager::LoadSaveFile(
		SaveManager::GetLocalProfileSaveFilePath(SaveManager::GetActiveSaveProfile()),
		SaveManager::GetCloudProfileSaveFilePath(SaveManager::GetActiveSaveProfile())
	);

	SaveManager::HasUnsavedChanges = false;
}

void SaveManager::Save()
{
	SaveManager::InitializeSaveData();

	// Save any uncommitted save data
	SaveManager::DoSave(
		SaveManager::ProfileSaveData,
		SaveManager::GetLocalProfileSaveFilePath(SaveManager::GetActiveSaveProfile()),
		SaveManager::GetCloudProfileSaveFilePath(SaveManager::GetActiveSaveProfile())
	);
}

void SaveManager::SaveGlobalData(std::string key, const Value& data)
{
	SaveManager::InitializeSaveData();

	SaveManager::GlobalSaveData[key] = data;

	SaveManager::DoSave(SaveManager::GlobalSaveData, SaveManager::GetLocalGlobalSaveFilePath(), SaveManager::GetCloudGlobalSaveFilePath());
}

void SaveManager::BatchSaveGlobalData(std::vector<std::tuple<std::string, cocos2d::Value>> newData)
{
	SaveManager::InitializeSaveData();

	for (auto next : newData)
	{
		SaveManager::GlobalSaveData[std::get<0>(next)] = std::get<1>(next);
	}

	SaveManager::DoSave(SaveManager::GlobalSaveData, SaveManager::GetLocalGlobalSaveFilePath(), SaveManager::GetCloudGlobalSaveFilePath());
}

void SaveManager::BatchSaveProfileData(std::vector<std::tuple<std::string, cocos2d::Value>> newData)
{
	SaveManager::InitializeSaveData();

	for (auto next : newData)
	{
		SaveManager::SoftSaveProfileData(std::get<0>(next), std::get<1>(next));
	}

	SaveManager::DoSave(
		SaveManager::ProfileSaveData,
		SaveManager::GetLocalProfileSaveFilePath(SaveManager::GetActiveSaveProfile()),
		SaveManager::GetCloudProfileSaveFilePath(SaveManager::GetActiveSaveProfile())
	);
}

void SaveManager::SoftSaveProfileData(std::string key, const Value& data)
{
	SaveManager::InitializeSaveData();

	if (SaveManager::ProfileSaveData.find(key) == SaveManager::ProfileSaveData.end() || SaveManager::ProfileSaveData[key] != data)
	{
		SaveManager::HasUnsavedChanges = true;
		SaveManager::ProfileSaveData[key] = data;
	}
}

void SaveManager::SaveProfileData(std::string key, const Value& data)
{
	SaveManager::InitializeSaveData();

	SaveManager::SoftSaveProfileData(key, data);

	SaveManager::DoSave(
		SaveManager::ProfileSaveData,
		SaveManager::GetLocalProfileSaveFilePath(SaveManager::GetActiveSaveProfile()),
		SaveManager::GetCloudProfileSaveFilePath(SaveManager::GetActiveSaveProfile())
	);
}

Value SaveManager::GetGlobalDataOrDefault(std::string key, const Value& defaultValue)
{
	SaveManager::InitializeSaveData();

	return GameUtils::getKeyOrDefault(SaveManager::GlobalSaveData, key, defaultValue);
}

Value SaveManager::GetGlobalData(std::string key)
{
	SaveManager::InitializeSaveData();

	return GameUtils::getKeyOrDefault(SaveManager::GlobalSaveData, key, Value());
}

Value SaveManager::GetProfileDataOrDefault(std::string key, const Value& defaultValue)
{
	SaveManager::InitializeSaveData();

	return GameUtils::getKeyOrDefault(SaveManager::ProfileSaveData, key, defaultValue);
}

Value SaveManager::GetProfileData(std::string key)
{
	SaveManager::InitializeSaveData();

	return GameUtils::getKeyOrDefault(SaveManager::ProfileSaveData, key, Value());
}

SaveManager::SaveProfile SaveManager::GetActiveSaveProfile()
{
	return SaveManager::ActiveSaveProfile;
}

void SaveManager::DoSave(ValueMap valueMap, std::string localSavePath, std::string cloudSavePath)
{
	if (!SaveManager::HasUnsavedChanges)
	{
		return;
	}

	// Increment save counter
	valueMap[SaveManager::SaveKeyIncrement] = GameUtils::getKeyOrDefault(valueMap, SaveManager::SaveKeyIncrement, Value(0)).asUnsignedInt() + 1;

	// Update saves in cache
	SaveManager::SaveFileCache[localSavePath] = valueMap;
	SaveManager::SaveFileCache[cloudSavePath] = valueMap;

	// Save to cloud if available
	if (Steam::IsCloudSaveAvailable())
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

				if (writeSuccess)
				{
					SaveManager::HasUnsavedChanges = false;
				}
				else
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

		if (writeSuccess)
		{
			SaveManager::HasUnsavedChanges = false;
		}
		else
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

ValueMap SaveManager::LoadSaveFile(std::string localSavePath, std::string cloudSavePath)
{
	ValueMap cloudValueMap = ValueMap();
	ValueMap localValueMap = ValueMap();
	
	if (SaveManager::SaveFileCache.find(cloudSavePath) == SaveManager::SaveFileCache.end())
	{
		bool cloudReadSuccess = false;

		// Load from cloud if it's available
		if (Steam::IsCloudSaveAvailable())
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
		cloudValueMap = SaveManager::SaveFileCache[cloudSavePath];
	}

	if (SaveManager::SaveFileCache.find(localSavePath) == SaveManager::SaveFileCache.end())
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
		localValueMap =	SaveManager::SaveFileCache[localSavePath];
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
	SaveManager::SaveFileCache[cloudSavePath] = returnValueMap;
	SaveManager::SaveFileCache[localSavePath] = returnValueMap;

	return returnValueMap;
}

bool SaveManager::HasSaveProfile(int profileId)
{
	ValueMap saveData = SaveManager::LoadSaveFile(
		SaveManager::GetLocalProfileSaveFilePath(profileId),
		SaveManager::GetCloudProfileSaveFilePath(profileId)
	);

	// If only the increment key is present, this is effectively an empty savefile
	if (saveData.size() == 1 && GameUtils::keyExists(saveData, SaveManager::SaveKeyIncrement))
	{
		return false;
	}

	return !saveData.empty();
}

void SaveManager::BatchDeleteProfileData(std::vector<std::string> keys)
{
	for (auto next : keys)
	{
		SaveManager::ProfileSaveData.erase(next);
	}

	SaveManager::DoSave(
		SaveManager::ProfileSaveData,
		SaveManager::GetLocalProfileSaveFilePath(SaveManager::GetActiveSaveProfile()),
		SaveManager::GetCloudProfileSaveFilePath(SaveManager::GetActiveSaveProfile())
	);
}

void SaveManager::SoftDeleteProfileData(std::string key)
{
	SaveManager::ProfileSaveData.erase(key);
}

void SaveManager::DeleteProfileData(std::string key)
{
	SaveManager::ProfileSaveData.erase(key);

	SaveManager::DoSave(
		SaveManager::ProfileSaveData,
		SaveManager::GetLocalProfileSaveFilePath(SaveManager::GetActiveSaveProfile()),
		SaveManager::GetCloudProfileSaveFilePath(SaveManager::GetActiveSaveProfile())
	);
}

void SaveManager::DeleteAllProfileData(int profileId)
{
	ValueMap oldSaveData = SaveManager::LoadSaveFile(
		SaveManager::GetLocalProfileSaveFilePath(profileId),
		SaveManager::GetCloudProfileSaveFilePath(profileId)
	);

	ValueMap wipedSave = ValueMap();

	// Copy the save increment from the old save file. Prevents clashing in the case where a save fails to delete on the cloud, but is deleted locally.
	wipedSave[SaveManager::SaveKeyIncrement] = GameUtils::getKeyOrDefault(oldSaveData, SaveManager::SaveKeyIncrement, Value(0));

	// Wipe save on disk
	SaveManager::DoSave(
		wipedSave,
		SaveManager::GetLocalProfileSaveFilePath(profileId),
		SaveManager::GetCloudProfileSaveFilePath(profileId)
	);
}

bool SaveManager::HasGlobalData(std::string key)
{
	return GameUtils::keyExists(SaveManager::GlobalSaveData, key);
}

bool SaveManager::HasProfileData(std::string key)
{
	return GameUtils::keyExists(SaveManager::ProfileSaveData, key);
}

std::string SaveManager::GetLocalGlobalSaveFilePath()
{
	return FileUtils::getInstance()->getWritablePath() + SaveManager::GlobalSaveFileName;
}

std::string SaveManager::GetLocalProfileSaveFilePath(int profileId)
{
	std::string fileName = StrUtils::replaceAll(SaveManager::ProfileSaveFileTemplate.c_str(), "%d", std::to_string(profileId));
	std::string fullPath = FileUtils::getInstance()->getWritablePath() + fileName;
	
	return fullPath;
}

std::string SaveManager::GetCloudGlobalSaveFilePath()
{
	// Raw filename is actually good enough as a path for cloud
	return SaveManager::GlobalSaveFileName;
}

std::string SaveManager::GetCloudProfileSaveFilePath(int profileId)
{
	std::string fileName = StrUtils::replaceAll(SaveManager::ProfileSaveFileTemplate.c_str(), "%d", std::to_string(profileId));

	// Raw filename is actually good enough as a path for cloud
	return fileName;
}
