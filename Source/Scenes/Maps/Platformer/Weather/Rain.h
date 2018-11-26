#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Maps/SerializableLayer.h"
#include "Resources/ParticleResources.h"

using namespace cocos2d;

class Rain : public SerializableLayer
{
public:
	static Rain * create(ValueMap* properties, std::string name);

	static const std::string KeyWeatherRain;

private:
	Rain(ValueMap* properties, std::string name);
	~Rain();

	void onEnter() override;
	void update(float) override;

	ParticleSystem * rain;
};
