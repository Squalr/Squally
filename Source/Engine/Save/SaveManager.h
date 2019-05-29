#pragma once

#include <map>
#include <string>
#include <vector>

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class SaveManager
{
public:
	typedef int ActiveSaveProfile;

	static void setActiveSaveProfile(ActiveSaveProfile activeSaveProfile);
	static void save();
	static void batchSaveGlobalData(std::vector<std::tuple<std::string, cocos2d::Value>> newData);
	static void saveGlobalData(std::string key, const cocos2d::Value& data);
	static void batchSaveProfileData(std::vector<std::tuple<std::string, cocos2d::Value>> newData);
	static void softSaveProfileData(std::string key, const cocos2d::Value& data);
	static void saveProfileData(std::string key, const cocos2d::Value& data);
	static cocos2d::Value getGlobalDataOrDefault(std::string key, const cocos2d::Value& defaultValue);
	static cocos2d::Value getGlobalData(std::string key);
	static cocos2d::Value getProfileDataOrDefault(std::string key, const cocos2d::Value& defaultValue);
	static cocos2d::Value getProfileData(std::string key);
	static void deleteAllProfileData(int profileId);
	static void batchDeleteProfileData(std::vector<std::string> keys);
	static void softDeleteProfileData(std::string key);
	static void deleteProfileData(std::string key);
	static bool hasSaveProfile(int profileId);
	static bool hasGlobalData(std::string key);
	static bool hasProfileData(std::string key);
	static ActiveSaveProfile getActiveSaveProfile();

private:
	SaveManager();
	~SaveManager();

	static void initializeSaveData();
	static void doSave(cocos2d::ValueMap valueMap, std::string localSavePath, std::string cloudSavePath);
	static cocos2d::ValueMap loadSaveFile(std::string localSavePath, std::string cloudSavePath);

	static std::string getLocalGlobalSaveFilePath();
	static std::string getLocalProfileSaveFilePath(int profileId);
	static std::string getCloudGlobalSaveFilePath();
	static std::string getCloudProfileSaveFilePath(int profileId);

	static std::map<std::string, cocos2d::ValueMap> saveFileCache;
	static ActiveSaveProfile activeSaveProfile;
	static cocos2d::ValueMap globalSaveData;
	static cocos2d::ValueMap profileSaveData;

	static const std::string globalSaveFileName;
	static const std::string profileSaveFileTemplate;
	static const std::string SaveKeyIncrement;
};
