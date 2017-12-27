#include "ConfigManager.h"

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
	this->loadConfigFileMap();
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::loadConfigFileMap()
{
	this->valueMap = FileUtils::getInstance()->getValueMapFromFile(FileUtils::sharedFileUtils()->getWritablePath() + "\\" + ConfigManager::ConfigFile);
}

void ConfigManager::save()
{
	FileUtils::getInstance()->writeValueMapToFile(this->valueMap, FileUtils::sharedFileUtils()->getWritablePath() + "\\" + ConfigManager::ConfigFile);
}

void ConfigManager::setResolution(ResolutionSetting resolution)
{
	GLViewImpl* glView = (GLViewImpl*)(Director::getInstance()->getOpenGLView());

	switch (resolution)
	{
	case R1080x768:
		glView->setWindowed(1080, 768);
		break;
	case R1152x864:
		glView->setWindowed(1152, 864);
		break;
	case R1280x720:
		glView->setWindowed(1280, 720);
		break;
	case R1280x960:
		glView->setWindowed(1280, 960);
		break;
	case R1280x1024:
		glView->setWindowed(1280, 1024);
		break;
	case R1440x900:
		glView->setWindowed(1440, 900);
		break;
	case R1600x900:
		glView->setWindowed(1600, 900);
		break;
	case R1600x1024:
		glView->setWindowed(1600, 1024);
		break;
	case R1920x1080:
		glView->setWindowed(1920, 1080);
		break;
	case ResolutionSetting::FullScreen:
	default:
		glView->setFullscreen();
		break;
	}

	glView->setDesignResolutionSize(glView->getFrameSize().width, glView->getFrameSize().height, ResolutionPolicy::NO_BORDER);

	this->valueMap[ConfigManager::ResolutionKey] = Value((int)resolution);
}

void ConfigManager::setSoundVolume(float volume)
{
	this->valueMap[ConfigManager::SoundVolumeKey] = volume;
}

void ConfigManager::setMusicVolume(float volume)
{
	this->valueMap[ConfigManager::MusicVolumeKey] = volume;
}

ConfigManager::ResolutionSetting ConfigManager::getResolution()
{
	if (!Utils::keyExists(this->valueMap, ConfigManager::ResolutionKey))
	{
		return ResolutionSetting::FullScreen;
	}
	else
	{
		return (ResolutionSetting)(this->valueMap[ConfigManager::ResolutionKey].asInt());
	}
}

float ConfigManager::getSoundVolume()
{
	if (Utils::keyExists(this->valueMap, ConfigManager::SoundVolumeKey))
	{
		return this->valueMap[ConfigManager::SoundVolumeKey].asFloat();
	}
	else
	{
		return 1.0f;
	}
}

float ConfigManager::getMusicVolume()
{
	if (Utils::keyExists(this->valueMap, ConfigManager::MusicVolumeKey))
	{
		return this->valueMap[ConfigManager::MusicVolumeKey].asFloat();
	}
	else
	{
		return 1.0f;
	}
}
