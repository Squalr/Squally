#pragma once
#include <string>
#include "cocos/platform/CCCommon.h"

class Steam
{
public:
	static bool init();
	static bool isSquallySteamBuild();
	static bool isSteamDebugBuild();
	static bool isCloudSaveAvailable();
	static cocos2d::LanguageType getLanguage();

	static const int SteamAppId;

private:
	static Steam* getInstance();

	Steam();
	~Steam();

	static bool isSteamLibPresent();

	static const std::string SteamLibOSX;
	static const std::string SteamLibWin32;
	static const std::string SteamLibWin64;
	static const std::string SteamLibLinux32;
	static Steam* instance;
};
