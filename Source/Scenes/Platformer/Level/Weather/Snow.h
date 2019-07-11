#pragma once
#include "Engine/Maps/MapLayer.h"

namespace cocos2d
{
	class ParticleSystem;
}

class Snow : public MapLayer
{
public:
	static Snow* create(cocos2d::ValueMap& properties, std::string name);

	static const std::string MapKeyWeatherLayerSnow;

private:
	typedef MapLayer super;
	Snow(cocos2d::ValueMap& properties, std::string name);
	~Snow();

	void onEnter() override;
	void update(float) override;

	cocos2d::ParticleSystem* snow;
};
