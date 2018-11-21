#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class SceneEvents
{
public:
	static void TriggerBeforeSceneChange();

	static const std::string BeforeSceneChangeEvent;
};
