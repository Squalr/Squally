#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Config/SoundManager.h"
#include "Utils/GameUtils.h"
#include "Level/Backgrounds/Backgrounds.h"
#include "Level/Environments/Environments.h"
#include "Level/Parser/Keys/EnvironmentKeys.h"
#include "Level/Parser/Keys/GeneralKeys.h"

using namespace cocos2d;

class EnvironmentParser
{
public:
	static Layer* parseBackground(TMXObjectGroup* objectGroup);
	static Layer* parseWeather(TMXObjectGroup* objectGroup);
	static void playMusic(TMXObjectGroup* objectGroup);
};
