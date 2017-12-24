#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class ConfigManager
{
public:
	static ConfigManager * GetInstance();

	enum ResolutionSetting
	{
		FullScreen,
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

	void SetResolution(ResolutionSetting resolution);
	void SetSoundVolume(float volume);
	void SetMusicVolume(float volume);

	ResolutionSetting GetResolution();
	float GetSoundVolume();
	float GetMusicVolume();

	void Save();

private:
	ConfigManager();
	~ConfigManager();

	void LoadConfigFileMap();

	ValueMap valueMap;

	static ConfigManager * configManagerInstance;

	const std::string ConfigFile = "config.txt";
	const std::string ResolutionKey = "resolution";
	const std::string SoundVolumeKey = "sound";
	const std::string MusicVolumeKey = "music";
};
