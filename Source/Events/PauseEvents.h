#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class PauseEvents
{
public:
	static const std::string PauseEvent;

	struct PauseEventArgs
	{
		std::string currentLevelFile;
		Vec2 pauseLocation;

		PauseEventArgs(std::string currentLevelFile, Vec2 pauseLocation) : currentLevelFile(currentLevelFile), pauseLocation(pauseLocation)
		{
		}
	};

	static void pauseLevel(PauseEventArgs args);
};
