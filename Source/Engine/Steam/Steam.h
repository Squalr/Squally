#pragma once
#include <string>

#include "cocos/platform/CCCommon.h"

class Steam
{
public:
	static bool Init();
	static bool IsSquallySteamBuild();
	static bool IsSteamDebugFilePresent();
	static bool IsCloudSaveAvailable();
	static std::string GetSteamUserId();
	static cocos2d::LanguageType GetLanguage();

	static const int SteamAppId;

protected:
	Steam();
	virtual ~Steam();

private:
	static Steam* GetInstance();

	static bool IsItchFilePresent();

	static const std::string ItchFile;
	static const std::string SteamDebugFile;
	static Steam* Instance;
};
