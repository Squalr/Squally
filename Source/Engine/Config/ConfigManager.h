#pragma once
#include "cocos/base/CCValue.h"
#include "cocos/math/CCGeometry.h"

class ConfigManager
{
public:
	enum class ResolutionSetting
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
		R2560x1440,
		R3840x2160,
	};

	enum class GraphicsSetting
	{
		SlowHighQuality,
		FastLowQuality
	};

	static void setResolution(ResolutionSetting resolution);
	static void setGraphics(GraphicsSetting graphics);
	static void setIsFullScreen(bool isFullscreen);
	static void setSoundVolume(float volume);
	static void setMusicVolume(float volume);

	static cocos2d::CSize getResolutionSize();
	static ResolutionSetting getResolution();
	static GraphicsSetting getGraphics();
	static bool getIsFullScreen();
	static float getSoundVolume();
	static float getMusicVolume();

	static bool hasLanguageSaved();
	static std::string getLanguage();
	static void setLanguage(std::string languageCode);

	static void save();

protected:
	ConfigManager();
	virtual ~ConfigManager();

private:
	static ConfigManager* getInstance();

	cocos2d::ValueMap valueMap;

	static ConfigManager* Instance;

	static const std::string ConfigFile;
	static const std::string ResolutionKey;
	static const std::string GraphicsKey;
	static const std::string FullScreenKey;
	static const std::string SoundVolumeKey;
	static const std::string MusicVolumeKey;
	static const std::string LanguageKey;
};
