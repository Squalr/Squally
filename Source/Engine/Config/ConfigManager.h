#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class ConfigManager
{
public:
	enum ResolutionSetting
	{
		R1080x768,
		R1152x864,
		R1280x720,
		R1280x960,
		R1280x1024,
		R1440x900,
		R1600x900,
		R1600x1024,
		R1920x1080,
	};

	static void setResolution(ResolutionSetting resolution);
	static void setIsFullScreen(bool isFullscreen);
	static void setSoundVolume(float volume);
	static void setMusicVolume(float volume);

	static Size getResolutionSize();
	static ResolutionSetting getResolution();
	static bool getIsFullScreen();
	static float getSoundVolume();
	static float getMusicVolume();

	static void save();

private:
	static ConfigManager * getInstance();
	ConfigManager();
	~ConfigManager();

	ValueMap valueMap;

	static ConfigManager * configManagerInstance;

	static const std::string ConfigFile;
	static const std::string ResolutionKey;
	static const std::string FullScreenKey;
	static const std::string SoundVolumeKey;
	static const std::string MusicVolumeKey;
};
