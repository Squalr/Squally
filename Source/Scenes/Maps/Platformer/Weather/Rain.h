#pragma once

#include "Engine/Maps/SerializableLayer.h"

namespace cocos2d
{
	class ParticleSystem;
}

class Rain : public SerializableLayer
{
public:
	static Rain* create(cocos2d::ValueMap* properties, std::string name);

	static const std::string MapKeyWeatherLayerRain;

private:
	typedef SerializableLayer super;
	Rain(cocos2d::ValueMap* properties, std::string name);
	~Rain();

	void onEnter() override;
	void update(float) override;

	cocos2d::ParticleSystem* rain;
};
