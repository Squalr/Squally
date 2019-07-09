#pragma once

#include "Engine/Maps/MapLayer.h"

using namespace cocos2d;

namespace cocos2d
{
	class ParticleSystem;
}

class Fireflies : public MapLayer
{
public:
	static Fireflies* create(cocos2d::ValueMap& properties, std::string name);

	static const std::string MapKeyWeatherLayerFireflies;

private:
	typedef MapLayer super;
	Fireflies(cocos2d::ValueMap& properties, std::string name);
	~Fireflies();

	void onEnter() override;
	void update(float) override;

	cocos2d::ParticleSystem* fireflies;
};
