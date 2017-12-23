#include "ConfigManager.h"

const Size* ConfigManager::Resolution1024x768 = new Size(1024, 768);
const Size* ConfigManager::Resolution1920x1080 = new Size(1920, 1080);

ConfigManager* ConfigManager::configManagerInstance = nullptr;

ConfigManager* ConfigManager::GetInstance()
{
	if (ConfigManager::configManagerInstance == nullptr)
	{
		ConfigManager::configManagerInstance = new ConfigManager();
	}

	return ConfigManager::configManagerInstance;
}

ConfigManager::ConfigManager()
{
	this->LoadConfigFileMap();
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::LoadConfigFileMap()
{
	this->valueMap = FileUtils::getInstance()->getValueMapFromFile(FileUtils::sharedFileUtils()->getWritablePath() + "\\" + ConfigManager::ConfigFile);
}

void ConfigManager::Save()
{
	FileUtils::getInstance()->writeValueMapToFile(this->valueMap, FileUtils::sharedFileUtils()->getWritablePath() + "\\" + ConfigManager::ConfigFile);
}

void ConfigManager::SetResolution(ResolutionSetting resolution)
{
	GLViewImpl* glView = (GLViewImpl*)(Director::getInstance()->getOpenGLView());

	switch (resolution)
	{
	case ResolutionSetting::R1080x768:
		glView->setWindowed(ConfigManager::Resolution1024x768->width, ConfigManager::Resolution1024x768->height);
		break;
	case ResolutionSetting::R1920x1080:
		glView->setWindowed(ConfigManager::Resolution1920x1080->width, ConfigManager::Resolution1920x1080->height);
		break;
	case ResolutionSetting::FullScreen:
	default:
		glView->setFullscreen();
	}

	glView->setDesignResolutionSize(glView->getFrameSize().width, glView->getFrameSize().height, ResolutionPolicy::NO_BORDER);

	this->valueMap[ConfigManager::ResolutionKey] = Value((int)resolution);
}

void ConfigManager::SetSoundVolume(float volume)
{
	this->valueMap[ConfigManager::SoundVolumeKey] = volume;
}

void ConfigManager::SetMusicVolume(float volume)
{
	this->valueMap[ConfigManager::MusicVolumeKey] = volume;
}

ConfigManager::ResolutionSetting ConfigManager::GetResolution()
{
	if (!Utils::KeyExists(this->valueMap, ConfigManager::ResolutionKey))
	{
		return  ResolutionSetting::FullScreen;
	}

	ResolutionSetting resolution = (ResolutionSetting)(this->valueMap[ConfigManager::ResolutionKey].asInt());

	switch (resolution)
	{
	case ResolutionSetting::R1080x768:
		return  ResolutionSetting::R1080x768;
		break;
	case ResolutionSetting::R1920x1080:
		return  ResolutionSetting::R1920x1080;
	case ResolutionSetting::FullScreen:
	default:
		return  ResolutionSetting::FullScreen;
	}
}

float ConfigManager::GetSoundVolume()
{
	if (Utils::KeyExists(this->valueMap, ConfigManager::SoundVolumeKey))
	{
		return this->valueMap[ConfigManager::SoundVolumeKey].asFloat();
	}
	else
	{
		return 1.0f;
	}
}

float ConfigManager::GetMusicVolume()
{
	if (Utils::KeyExists(this->valueMap, ConfigManager::MusicVolumeKey))
	{
		return this->valueMap[ConfigManager::MusicVolumeKey].asFloat();
	}
	else
	{
		return 1.0f;
	}
}
