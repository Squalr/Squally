#pragma once
#include "Engine/Maps/SerializableLayer.h"

namespace cocos2d
{
	class ParticleSystem;
}

class Snow : public SerializableLayer
{
public:
	static Snow* create(cocos2d::ValueMap* properties, std::string name);

	static const std::string MapKeyWeatherLayerSnow;

private:
	Snow(cocos2d::ValueMap* properties, std::string name);
	~Snow();

	void onEnter() override;
	void update(float) override;

	cocos2d::ParticleSystem* snow;
};
