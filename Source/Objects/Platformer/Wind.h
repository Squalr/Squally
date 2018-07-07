#pragma once
#include "cocos2d.h"

#include "Engine/Objects/Hackables/HackableObject.h"

using namespace cocos2d;

class Wind : public HackableObject
{
public:
	static Wind* create(ValueMap* initProperties);

protected:
	Wind(ValueMap* initProperties);
	~Wind();

private:
	void registerHackables();

	void update(float) override;

	HackableData * windDataSpeedY;
	ParticleSystem * windParticles;
	Vec2 windSpeed;
};
