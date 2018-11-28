#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Maps/SerializableLayer.h"
#include "Resources/ParticleResources.h"

using namespace cocos2d;

class Fireflies : public SerializableLayer
{
public:
	static Fireflies* create(ValueMap* properties, std::string name);

	static const std::string MapKeyWeatherLayerFireflies;

private:
	Fireflies(ValueMap* properties, std::string name);
	~Fireflies();

	void onEnter() override;
	void update(float) override;

	ParticleSystem* fireflies;
};
