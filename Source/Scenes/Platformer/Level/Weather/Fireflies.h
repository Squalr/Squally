#pragma once

#include "Engine/Maps/MapLayer.h"

using namespace cocos2d;

class SmartParticles;

class Fireflies : public MapLayer
{
public:
	static Fireflies* create(cocos2d::ValueMap& properties, std::string name);

	static const std::string MapKeyWeatherLayerFireflies;

protected:
	Fireflies(cocos2d::ValueMap& properties, std::string name);
	virtual ~Fireflies();

	void onEnter() override;
	void update(float) override;

private:
	typedef MapLayer super;

	SmartParticles* fireflies;
};
