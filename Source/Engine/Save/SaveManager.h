#pragma once
#include "cocos2d.h"

#include "Engine/Steam/Steam.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

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

	static void doSave(ValueMap valueMap, std::string localSavePath, std::string cloudSavePath);
	static ValueMap loadSaveFile(std::string localSavePath, std::string cloudSavePath);

	std::string getLocalGlobalSaveFilePath();
	std::string getLocalActiveProfileSaveFilePath();
	std::string getCloudGlobalSaveFilePath();
	std::string getCloudActiveProfileSaveFilePath();

	ActiveSaveProfile activeSaveProfile;
	ValueMap globalSaveData;
	ValueMap profileSaveData;

	static SaveManager *instance;
	static const std::string globalSaveFileName;
	static const std::string profileSaveFileTemplate;
	static const std::string SaveKeyIncrement;
};
