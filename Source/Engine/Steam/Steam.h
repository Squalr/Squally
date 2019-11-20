#pragma once
#include <string>
#include "cocos/platform/CCCommon.h"

class Steam
{
public:
	static bool init();
	static bool isSquallySteamBuild();
	static bool isSteamDebugFilePresent();
	static bool isCloudSaveAvailable();
	static std::string getSteamUserId();
	static cocos2d::LanguageType getLanguage();

	static const int SteamAppId;

private:
	static Steam* getInstance();

	Steam();
	~Steam();

	static bool isItchFilePresent();

	static const std::string ItchFile;
	static const std::string SteamDebugFile;
	static Steam* instance;
};
