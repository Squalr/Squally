#pragma once
#include "cocos2d.h"

#include "Scenes/Level/LevelCamera.h"
#include "Engine/Maps/SerializableLayer.h"

using namespace cocos2d;

class Fireflies : public SerializableLayer
{
public:
	static Fireflies * create(std::string name, ValueMap properties);

	static const std::string KeyWeatherFireflies;

private:
	Fireflies(std::string name, ValueMap properties);
	~Fireflies();

	void onEnter() override;
	void update(float) override;

	ParticleSystem * fireflies;
};
