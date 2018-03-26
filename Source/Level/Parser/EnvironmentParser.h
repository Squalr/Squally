#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"
#include "Level/Backgrounds/JungleBackground.h"
#include "Level/Backgrounds/MountainBackground.h"
#include "Level/Environments/JungleEnvironment.h"

using namespace cocos2d;

class EnvironmentParser
{
public:
	static Layer* parseBackground(TMXObjectGroup* objectGroup);
	static Layer* parseWeather(TMXObjectGroup* objectGroup);
	static Layer* parseMusic(TMXObjectGroup* objectGroup);

};
