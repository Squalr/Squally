#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Maps/SerializableLayer.h"

using namespace cocos2d;

class Snow : public SerializableLayer
{
public:
	static Snow * create(ValueMap* properties, std::string name);

	static const std::string KeyWeatherSnow;

private:
	Snow(ValueMap* properties, std::string name);
	~Snow();

	void onEnter() override;
	void update(float) override;

	ParticleSystem * snow;
};
