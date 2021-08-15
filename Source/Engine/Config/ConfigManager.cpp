#include "ConfigManager.h"

#include "cocos/platform/CCFileUtils.h"
#include "cocos/platform/desktop/CCGLViewImpl-desktop.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const std::string ConfigManager::ConfigFile = "config.txt";
const std::string ConfigManager::ResolutionKey = "resolution";
const std::string ConfigManager::GraphicsKey = "graphics";
const std::string ConfigManager::FullScreenKey = "fullscreen";
const std::string ConfigManager::SoundVolumeKey = "sound";
const std::string ConfigManager::MusicVolumeKey = "music";
const std::string ConfigManager::LanguageKey = "language";

ConfigManager* ConfigManager::Instance = nullptr;

ConfigManager* ConfigManager::getInstance()
{
	if (ConfigManager::Instance == nullptr)
	{
		ConfigManager::Instance = new ConfigManager();
	}

	return ConfigManager::Instance;
}

ConfigManager::ConfigManager()
{
	try
	{
		this->valueMap = FileUtils::getInstance()->getValueMapFromFile(
				FileUtils::getInstance()->getWritablePath() + "/" + ConfigManager::ConfigFile);
	}
	catch (...)
	{
		this->valueMap = ValueMap();
	}
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::save()
{
	ConfigManager* Instance = ConfigManager::getInstance();

	try
	{
		FileUtils::getInstance()->writeValueMapToFile(Instance->valueMap,
				FileUtils::getInstance()->getWritablePath() + "/" + ConfigManager::ConfigFile);
	}
	catch (...)
	{
	}
}

bool ConfigManager::hasLanguageSaved()
{
	return GameUtils::keyExists(ConfigManager::getInstance()->valueMap, ConfigManager::LanguageKey);
}

std::string ConfigManager::getLanguage()
{
	if (GameUtils::keyExists(ConfigManager::getInstance()->valueMap, ConfigManager::LanguageKey))
	{
		return ConfigManager::getInstance()->valueMap[ConfigManager::LanguageKey].asString();
	}

	return "en";
}

void ConfigManager::setLanguage(std::string languageCode)
{
	ConfigManager::getInstance()->valueMap[ConfigManager::LanguageKey] = Value(languageCode);
}

void ConfigManager::setResolution(ResolutionSetting resolution)
{
	ConfigManager* Instance = ConfigManager::getInstance();
	GLViewImpl* glView = (GLViewImpl*)(Director::getInstance()->getOpenGLView());

	Instance->valueMap[ConfigManager::ResolutionKey] = Value((int)resolution);

	cocos2d::CSize resolutionSize = ConfigManager::getResolutionSize();

	if (ConfigManager::getIsFullScreen())
	{
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
		glView->setContentScaleFactor(0.5f);
	}
	else
	{
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
		glView->setWindowed(int(resolutionSize.width), int(resolutionSize.height));
	}
}

void ConfigManager::setGraphics(GraphicsSetting graphics)
{
	ConfigManager* Instance = ConfigManager::getInstance();

	Instance->valueMap[ConfigManager::GraphicsKey] = Value((int)graphics);
}

void ConfigManager::setIsFullScreen(bool isFullScreen)
{
	ConfigManager* Instance = ConfigManager::getInstance();
	GLViewImpl* glView = (GLViewImpl*)(Director::getInstance()->getOpenGLView());
	cocos2d::CSize resolutionSize = ConfigManager::getResolutionSize();

	if (isFullScreen)
	{
		glView->setFullscreen();
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}
	else
	{

		glView->setWindowed(int(resolutionSize.width), int(resolutionSize.height));
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}

	Instance->valueMap[ConfigManager::FullScreenKey] = isFullScreen;
}

void ConfigManager::setSoundVolume(float volume)
{
	ConfigManager* Instance = ConfigManager::getInstance();

	Instance->valueMap[ConfigManager::SoundVolumeKey] = MathUtils::clamp(volume, 0.0f, 1.0f);

	SoundEvents::TriggerSoundVolumeUpdated();
}

void ConfigManager::setMusicVolume(float volume)
{
	ConfigManager* Instance = ConfigManager::getInstance();

	Instance->valueMap[ConfigManager::MusicVolumeKey] = MathUtils::clamp(volume, 0.0f, 1.0f);

	SoundEvents::TriggerMusicVolumeUpdated();
}

cocos2d::CSize ConfigManager::getResolutionSize()
{
	cocos2d::CSize size = cocos2d::CSize();

	switch (ConfigManager::getResolution())
	{
		case ResolutionSetting::R1080x768:
		{
			size.width = 1080;
			size.height = 768;
			break;
		}
		case ResolutionSetting::R1152x864:
		{
			size.width = 1152;
			size.height = 864;
			break;
		}
		case ResolutionSetting::R1280x720:
		{
			size.width = 1280;
			size.height = 720;
			break;
		}
		case ResolutionSetting::R1280x960:
		{
			size.width = 1280;
			size.height = 960;
			break;
		}
		case ResolutionSetting::R1280x1024:
		{
			size.width = 1280;
			size.height = 1024;
			break;
		}
		case ResolutionSetting::R1440x900:
		{
			size.width = 1440;
			size.height = 900;
			break;
		}
		case ResolutionSetting::R1600x900:
		{
			size.width = 1600;
			size.height = 900;
			break;
		}
		case ResolutionSetting::R1600x1024:
		{
			size.width = 1600;
			size.height = 1024;
			break;
		}
		case ResolutionSetting::R1920x1080:
		{
			size.width = 1920;
			size.height = 1080;
			break;
		}
		case ResolutionSetting::R2560x1440:
		{
			size.width = 2560;
			size.height = 1440;
			break;
		}
		case ResolutionSetting::R3840x2160:
		{
			size.width = 3840;
			size.height = 2160;
			break;
		}
		default:
		{
			break;
		}
	}

	return size;
}

ConfigManager::ResolutionSetting ConfigManager::getResolution()
{
	ConfigManager* Instance = ConfigManager::getInstance();

	return (ResolutionSetting)GameUtils::getKeyOrDefault(Instance->valueMap, ConfigManager::ResolutionKey, Value((int)ResolutionSetting::R1080x768)).asInt();
}

ConfigManager::GraphicsSetting ConfigManager::getGraphics()
{
	ConfigManager* Instance = ConfigManager::getInstance();

	return (GraphicsSetting)GameUtils::getKeyOrDefault(Instance->valueMap, ConfigManager::GraphicsKey, Value((int)GraphicsSetting::SlowHighQuality)).asInt();
}

bool ConfigManager::getIsFullScreen()
{
	ConfigManager* Instance = ConfigManager::getInstance();

	return GameUtils::getKeyOrDefault(Instance->valueMap, ConfigManager::FullScreenKey, Value(false)).asBool();
}

float ConfigManager::getSoundVolume()
{
	ConfigManager* Instance = ConfigManager::getInstance();

	return GameUtils::getKeyOrDefault(Instance->valueMap, ConfigManager::SoundVolumeKey, Value(0.5f)).asFloat();
}

float ConfigManager::getMusicVolume()
{
	ConfigManager* Instance = ConfigManager::getInstance();

	return GameUtils::getKeyOrDefault(Instance->valueMap, ConfigManager::MusicVolumeKey, Value(0.5f)).asFloat();
}
