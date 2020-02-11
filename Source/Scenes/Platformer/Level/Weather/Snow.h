#pragma once
#include "Engine/Maps/MapLayer.h"

class SmartParticles;

class Snow : public MapLayer
{
public:
	static Snow* create(cocos2d::ValueMap& properties, std::string name);

	static const std::string MapKeyWeatherLayerSnow;

protected:
	Snow(cocos2d::ValueMap& properties, std::string name);
	virtual ~Snow();

	void onEnter() override;
	void update(float) override;

private:
	typedef MapLayer super;

	SmartParticles* snow;
};
