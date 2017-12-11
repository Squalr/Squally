#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class ConfigManager
{
public:
	enum ResolutionSetting {
		FullScreen,
		R1080x768,
		R1920x1080,
	};

	static void SetResolution(ResolutionSetting resolution);

	static ResolutionSetting LoadResolution();

	const static Size* Resolution1024x768;
	const static Size* Resolution1920x1080;
};
