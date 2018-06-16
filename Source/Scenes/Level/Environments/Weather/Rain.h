#pragma once
#include "cocos2d.h"

#include "Scenes/Level/LevelCamera.h"
#include "Engine/Maps/SerializableLayer.h"

using namespace cocos2d;

class Rain : public SerializableLayer
{
public:
	static Rain * create(std::string name, ValueMap properties);

	static const std::string KeyWeatherRain;

private:
	Rain(std::string name, ValueMap properties);
	~Rain();

	void onEnter() override;
	void update(float) override;

	ParticleSystem * rain;
};
