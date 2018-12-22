#pragma once
#include "cocos/platform/CCCommon.h"

class Steam
{
public:
	static bool isSteamEnabled();
	static bool isCloudSaveAvailable();
	static cocos2d::LanguageType getLanguage();

	static const int SteamAppId;

private:
	static Steam* getInstance();

	Steam();
	~Steam();

	static Steam* instance;
};
