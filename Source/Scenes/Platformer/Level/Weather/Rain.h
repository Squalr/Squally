#pragma once

#include "Engine/Particles/SmartParticles.h"
#include "Engine/Maps/MapLayer.h"

class SmartParticles;

class Rain : public MapLayer
{
public:
	static Rain* create(cocos2d::ValueMap& properties, std::string name);

	static const std::string MapKeyWeatherLayerRain;

protected:
	Rain(cocos2d::ValueMap& properties, std::string name);
	virtual ~Rain();

	void onEnter() override;
	void update(float) override;

private:
	typedef MapLayer super;

	SmartParticles* rain;
};
