#pragma once
#include "cocos2d.h"

#include "Engine/Sound/SoundManager.h"
#include "Resources.h"
#include "Scenes/Level/Backgrounds/Backgrounds.h"
#include "Scenes/Level/Environments/Environments.h"
#include "Utils/GameUtils.h"

#include "Keys/EnvironmentKeys.h"
#include "Keys/GeneralKeys.h"

using namespace cocos2d;

class EnvironmentParser
{
public:
	static Layer* parseBackground(TMXObjectGroup* objectGroup);
	static Layer* parseWeather(TMXObjectGroup* objectGroup);
	static void playMusic(TMXObjectGroup* objectGroup);
};
