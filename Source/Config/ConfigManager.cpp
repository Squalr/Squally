#include "ConfigManager.h"

const Size* ConfigManager::Resolution1024x768 = new Size(1024, 768);
const Size* ConfigManager::Resolution1920x1080 = new Size(1920, 1080);

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
