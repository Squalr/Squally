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
	static void BatchSaveGlobalData(const std::vector<std::tuple<std::string, cocos2d::Value>>& newData);
	static void SaveGlobalData(const std::string& key, const cocos2d::Value& data);
	static void BatchSaveProfileData(const std::vector<std::tuple<std::string, cocos2d::Value>>& newData);
	static void SoftSaveProfileData(const std::string& key, const cocos2d::Value& data);
	static void SaveProfileData(const std::string& key, const cocos2d::Value& data);
	static cocos2d::Value GetGlobalDataOrDefault(const std::string& key, const cocos2d::Value& defaultValue);
	static cocos2d::Value GetGlobalData(const std::string& key);
	static cocos2d::Value GetProfileDataOrDefault(const std::string& key, const cocos2d::Value& defaultValue);
	static cocos2d::Value GetProfileData(const std::string& key);
	static void DeleteAllProfileData(int profileId);
	static void BatchDeleteProfileData(const std::vector<std::string>& keys);
	static void SoftDeleteProfileData(const std::string& key);
	static void DeleteProfileData(const std::string& key);
	static bool HasSaveProfile(int profileId);
	static bool HasGlobalData(const std::string& key);
	static bool HasProfileData(const std::string& key);
	static SaveProfile GetActiveSaveProfile();

protected:
	SaveManager();
	virtual ~SaveManager();

private:
	static void InitializeSaveData();
	static void DoSave(cocos2d::ValueMap valueMap, const std::string& localSavePath, const std::string& cloudSavePath);
	static cocos2d::ValueMap LoadSaveFile(const std::string& localSavePath, const std::string& cloudSavePath);

	static const std::string& GetLocalGlobalSaveFilePath();
	static const std::string& GetLocalProfileSaveFilePath(int profileId);
	static const std::string& GetCloudGlobalSaveFilePath();
	static const std::string& GetCloudProfileSaveFilePath(int profileId);

	static std::map<std::string, cocos2d::ValueMap> SaveFileCache;
	static SaveProfile ActiveSaveProfile;
	static cocos2d::ValueMap GlobalSaveData;
	static cocos2d::ValueMap ProfileSaveData;

	static const std::string GlobalSaveFileName;
	static const std::string ProfileSaveFileTemplate;
	static const std::string SaveKeyIncrement;

	static bool HasUnsavedChanges;
};
