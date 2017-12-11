#include "ConfigManager.h"

const Size* ConfigManager::Resolution1024x768 = new Size(1024, 768);
const Size* ConfigManager::Resolution1920x1080 = new Size(1920, 1080);

GLViewImpl* ConfigManager::glView = nullptr;

void ConfigManager::SetGlView(GLViewImpl* currentGlView)
{
	ConfigManager::glView = currentGlView;
}

void ConfigManager::SetResolution(ResolutionSetting resolution)
{
	switch (resolution)
	{
	case ResolutionSetting::R1080x768:
		ConfigManager::glView->setWindowed(1080, 768);
		break;
	case ResolutionSetting::R1920x1080:
		ConfigManager::glView->setWindowed(1920, 1080);
		break;
	case ResolutionSetting::FullScreen:
	default:
		ConfigManager::glView->setFullscreen();
	}

	ConfigManager::glView->setDesignResolutionSize(ConfigManager::glView->getFrameSize().width, ConfigManager::glView->getFrameSize().height, ResolutionPolicy::NO_BORDER);

	ValueMap valueMap;

	valueMap["resolution"] = Value((int)resolution);

	FileUtils::getInstance()->writeValueMapToFile(valueMap, FileUtils::sharedFileUtils()->getWritablePath() + "\\resolution.txt");
}

ConfigManager::ResolutionSetting ConfigManager::LoadResolution()
{
	ValueMap valueMap = FileUtils::getInstance()->getValueMapFromFile(FileUtils::sharedFileUtils()->getWritablePath() + "\\resolution.txt");

	ResolutionSetting resolution = (ResolutionSetting)(valueMap["resolution"].asInt());

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
