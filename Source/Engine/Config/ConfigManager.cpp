#include "ConfigManager.h"

const std::string ConfigManager::ConfigFile = "config.txt";
const std::string ConfigManager::ResolutionKey = "resolution";
const std::string ConfigManager::FullScreenKey = "fullscreen";
const std::string ConfigManager::SoundVolumeKey = "sound";
const std::string ConfigManager::MusicVolumeKey = "music";

ConfigManager* ConfigManager::configManagerInstance = nullptr;

ConfigManager* ConfigManager::getInstance()
{
	if (ConfigManager::configManagerInstance == nullptr)
	{
		ConfigManager::configManagerInstance = new ConfigManager();
	}

	return ConfigManager::configManagerInstance;
}

ConfigManager::ConfigManager()
{
	this->valueMap = FileUtils::getInstance()->getValueMapFromFile(FileUtils::sharedFileUtils()->getWritablePath() + "\\" + ConfigManager::ConfigFile);
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::save()
{
	ConfigManager* instance = ConfigManager::getInstance();

	FileUtils::getInstance()->writeValueMapToFile(instance->valueMap, FileUtils::sharedFileUtils()->getWritablePath() + "\\" + ConfigManager::ConfigFile);
}

void ConfigManager::setResolution(ResolutionSetting resolution)
{
	ConfigManager* instance = ConfigManager::getInstance();
	GLViewImpl* glView = (GLViewImpl*)(Director::getInstance()->getOpenGLView());

	instance->valueMap[ConfigManager::ResolutionKey] = Value((int)resolution);

	Size resolutionSize = ConfigManager::getResolutionSize();

	if (ConfigManager::getIsFullScreen())
	{
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
		glView->setContentScaleFactor(0.5f);
	}
	else
	{
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
		glView->setWindowed(resolutionSize.width, resolutionSize.height);
	}
}

void ConfigManager::setIsFullScreen(bool isFullScreen)
{
	ConfigManager* instance = ConfigManager::getInstance();
	GLViewImpl* glView = (GLViewImpl*)(Director::getInstance()->getOpenGLView());
	Size resolutionSize = ConfigManager::getResolutionSize();

	if (isFullScreen)
	{
		glView->setFullscreen();
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}
	else
	{

		glView->setWindowed(resolutionSize.width, resolutionSize.height);
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}

	instance->valueMap[ConfigManager::FullScreenKey] = isFullScreen;
}

void ConfigManager::setSoundVolume(float volume)
{
	ConfigManager* instance = ConfigManager::getInstance();

	instance->valueMap[ConfigManager::SoundVolumeKey] = volume;
}

void ConfigManager::setMusicVolume(float volume)
{
	ConfigManager* instance = ConfigManager::getInstance();

	instance->valueMap[ConfigManager::MusicVolumeKey] = volume;
}

Size ConfigManager::getResolutionSize()
{
	Size size = Size();

	switch (ConfigManager::getResolution())
	{
	case R1080x768:
		size.width = 1080;
		size.height = 768;
		break;
	case R1152x864:
		size.width = 1152;
		size.height = 864;
		break;
	case R1280x720:
		size.width = 1280;
		size.height = 720;
		break;
	case R1280x960:
		size.width = 1280;
		size.height = 960;
		break;
	case R1280x1024:
		size.width = 1280;
		size.height = 1024;
		break;
	case R1440x900:
		size.width = 1440;
		size.height = 900;
		break;
	case R1600x900:
		size.width = 1600;
		size.height = 900;
		break;
	case R1600x1024:
		size.width = 1600;
		size.height = 1024;
		break;
	case R1920x1080:
		size.width = 1920;
		size.height = 1080;
		break;
	case R2560x1440:
		size.width = 2560;
		size.height = 1440;
		break;
	case R3840x2160:
		size.width = 3840;
		size.height = 2160;
		break;
	default:
		break;
	}

	return size;
}

ConfigManager::ResolutionSetting ConfigManager::getResolution()
{
	ConfigManager* instance = ConfigManager::getInstance();

	if (!GameUtils::keyExists(&instance->valueMap, ConfigManager::ResolutionKey))
	{
		return ResolutionSetting::R1920x1080;
	}
	else
	{
		return (ResolutionSetting)(instance->valueMap[ConfigManager::ResolutionKey].asInt());
	}
}

bool ConfigManager::getIsFullScreen()
{
	ConfigManager* instance = ConfigManager::getInstance();

	if (!GameUtils::keyExists(&instance->valueMap, ConfigManager::FullScreenKey))
	{
		return true;
	}
	else
	{
		return instance->valueMap[ConfigManager::FullScreenKey].asBool();
	}
}

float ConfigManager::getSoundVolume()
{
	ConfigManager* instance = ConfigManager::getInstance();

	if (GameUtils::keyExists(&instance->valueMap, ConfigManager::SoundVolumeKey))
	{
		return instance->valueMap[ConfigManager::SoundVolumeKey].asFloat();
	}
	else
	{
		return 0.5f;
	}
}

float ConfigManager::getMusicVolume()
{
	ConfigManager* instance = ConfigManager::getInstance();

	if (GameUtils::keyExists(&instance->valueMap, ConfigManager::MusicVolumeKey))
	{
		return instance->valueMap[ConfigManager::MusicVolumeKey].asFloat();
	}
	else
	{
		return 0.5f;
	}
}
