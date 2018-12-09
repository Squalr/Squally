#pragma once
#include "cocos/base/CCValue.h"

class SaveManager
{
public:
	typedef int ActiveSaveProfile;

	static void setActiveSaveProfile(ActiveSaveProfile activeSaveProfile);
	static void saveGlobalData(std::string key, cocos2d::Value data);
	static void saveProfileData(std::string key, cocos2d::Value data);
	static cocos2d::Value getGlobalDataOrDefault(std::string key, cocos2d::Value defaultValue);
	static cocos2d::Value getGlobalData(std::string key);
	static cocos2d::Value getProfileDataOrDefault(std::string key, cocos2d::Value defaultValue);
	static cocos2d::Value getProfileData(std::string key);
	static bool hasGlobalData(std::string key);
	static bool hasProfileData(std::string key);
	static ActiveSaveProfile getActiveSaveProfile();

private:
	static SaveManager* getInstance();
	SaveManager();
	~SaveManager();
	void initialize();

	static void doSave(cocos2d::ValueMap valueMap, std::string localSavePath, std::string cloudSavePath);
	static cocos2d::ValueMap loadSaveFile(std::string localSavePath, std::string cloudSavePath);

	std::string getLocalGlobalSaveFilePath();
	std::string getLocalActiveProfileSaveFilePath();
	std::string getCloudGlobalSaveFilePath();
	std::string getCloudActiveProfileSaveFilePath();

	ActiveSaveProfile activeSaveProfile;
	cocos2d::ValueMap globalSaveData;
	cocos2d::ValueMap profileSaveData;

	static SaveManager *instance;
	static const std::string globalSaveFileName;
	static const std::string profileSaveFileTemplate;
	static const std::string SaveKeyIncrement;
};
