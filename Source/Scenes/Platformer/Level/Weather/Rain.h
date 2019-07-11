#pragma once

#include "Engine/Maps/MapLayer.h"

namespace cocos2d
{
	class ParticleSystem;
}

class Rain : public MapLayer
{
public:
	static Rain* create(cocos2d::ValueMap& properties, std::string name);

	static const std::string MapKeyWeatherLayerRain;

private:
	typedef MapLayer super;
	Rain(cocos2d::ValueMap& properties, std::string name);
	~Rain();

	void onEnter() override;
	void update(float) override;

	cocos2d::ParticleSystem* rain;
};
