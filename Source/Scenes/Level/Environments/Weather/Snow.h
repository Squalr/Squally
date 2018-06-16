#pragma once
#include "cocos2d.h"

#include "Scenes/Level/LevelCamera.h"
#include "Engine/Maps/SerializableLayer.h"

using namespace cocos2d;

class Snow : public SerializableLayer
{
public:
	static Snow * create(std::string name, ValueMap properties);

	static const std::string KeyWeatherSnow;

private:
	Snow(std::string name, ValueMap properties);
	~Snow();

	void onEnter() override;
	void update(float) override;

	ParticleSystem * snow;
};
