#pragma once
#include "cocos2d.h"

#include "Engine/Sound/SoundManager.h"
#include "Objects/SerializableLayer.h"
#include "Resources.h"
#include "Scenes/Level/Backgrounds/Backgrounds.h"
#include "Scenes/Level/Environments/Environments.h"
#include "Scenes/Level/Parser/Keys/EnvironmentKeys.h"
#include "Scenes/Level/Parser/Keys/GeneralKeys.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class EnvironmentParser
{
public:
	static SerializableLayer* parseBackground(TMXObjectGroup* objectGroup);
	static SerializableLayer* parseWeather(TMXObjectGroup* objectGroup);
	static void playMusic(TMXObjectGroup* objectGroup);
};
