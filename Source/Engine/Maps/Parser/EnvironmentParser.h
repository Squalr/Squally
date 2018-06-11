#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/Keys/EnvironmentKeys.h"
#include "Engine/Maps/Keys/GeneralKeys.h"
#include "Engine/Sound/SoundManager.h"
#include "Resources.h"
#include "Scenes/Level/Backgrounds/Backgrounds.h"
#include "Scenes/Level/Environments/Environments.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class EnvironmentParser
{
public:
	static SerializableLayer* parseBackground(TMXObjectGroup* objectGroup);
	static SerializableLayer* parseWeather(TMXObjectGroup* objectGroup);
	static void playMusic(TMXObjectGroup* objectGroup);
};
