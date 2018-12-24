#pragma once

#include "Engine/Hackables/HackableObject.h"

class HackableData;

namespace cocos2d
{
	class ParticleSystem;
}

class Wind : public HackableObject
{
public:
	static Wind* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyWind;

protected:
	Wind(cocos2d::ValueMap* initProperties);
	~Wind();

	cocos2d::Vec2 getButtonOffset() override;

private:
	void registerHackables();

	void update(float) override;

	HackableData* windDataSpeedY;
	cocos2d::ParticleSystem* windParticles;
	cocos2d::Vec2 windSpeed;
};
