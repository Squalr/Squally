#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Sound/SoundManager.h"
#include "Resources.h"
#include "Scenes/Level/Backgrounds/Backgrounds.h"
#include "Scenes/Level/Environments/Environments.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class EnvironmentDeserializer
{
public:
	static SerializableLayer* deserializeBackground(TMXObjectGroup* objectGroup);
	static SerializableLayer* deserializeWeather(TMXObjectGroup* objectGroup);
	static void playMusic(TMXObjectGroup* objectGroup);

	static const std::string KeyBackgroundProperty;
	static const std::string KeyBackgroundJungle;
	static const std::string KeyBackgroundSnow;
	static const std::string KeyBackgroundOcean;
	static const std::string KeyBackgroundMountain;

	static const std::string KeyWeatherProperty;
	static const std::string KeyWeatherSnow;
	static const std::string KeyWeatherRain;

	static const std::string KeyMusicProperty;
};
