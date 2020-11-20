#pragma once

#include <map>
#include <string>
#include <vector>

#include "cocos/base/CCValue.h"

class SaveManager
{
public:
	typedef int SaveProfile;

	static void SetActiveSaveProfile(SaveProfile ActiveSaveProfile);
	static void Save();
	static void BatchSaveGlobalData(std::vector<std::tuple<std::string, cocos2d::Value>> newData);
	static void SaveGlobalData(std::string key, const cocos2d::Value& data);
	static void BatchSaveProfileData(std::vector<std::tuple<std::string, cocos2d::Value>> newData);
	static void SoftSaveProfileData(std::string key, const cocos2d::Value& data);
	static void SaveProfileData(std::string key, const cocos2d::Value& data);
	static cocos2d::Value GetGlobalDataOrDefault(std::string key, const cocos2d::Value& defaultValue);
	static cocos2d::Value GetGlobalData(std::string key);
	static cocos2d::Value GetProfileDataOrDefault(std::string key, const cocos2d::Value& defaultValue);
	static cocos2d::Value GetProfileData(std::string key);
	static void DeleteAllProfileData(int profileId);
	static void BatchDeleteProfileData(std::vector<std::string> keys);
	static void SoftDeleteProfileData(std::string key);
	static void DeleteProfileData(std::string key);
	static bool HasSaveProfile(int profileId);
	static bool HasGlobalData(std::string key);
	static bool HasProfileData(std::string key);
	static SaveProfile GetActiveSaveProfile();

protected:
	SaveManager();
	virtual ~SaveManager();

private:
	static void InitializeSaveData();
	static void DoSave(cocos2d::ValueMap valueMap, std::string localSavePath, std::string cloudSavePath);
	static cocos2d::ValueMap LoadSaveFile(std::string localSavePath, std::string cloudSavePath);

	static std::string GetLocalGlobalSaveFilePath();
	static std::string GetLocalProfileSaveFilePath(int profileId);
	static std::string GetCloudGlobalSaveFilePath();
	static std::string GetCloudProfileSaveFilePath(int profileId);

	static std::map<std::string, cocos2d::ValueMap> SaveFileCache;
	static SaveProfile ActiveSaveProfile;
	static cocos2d::ValueMap GlobalSaveData;
	static cocos2d::ValueMap ProfileSaveData;

	static const std::string GlobalSaveFileName;
	static const std::string ProfileSaveFileTemplate;
	static const std::string SaveKeyIncrement;

	static bool HasUnsavedChanges;
};
