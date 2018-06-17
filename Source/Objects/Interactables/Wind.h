#pragma once
#include "cocos2d.h"

#include "Objects/Collision/CollisionObject.h"

using namespace cocos2d;

class Wind : public CollisionObject
{
public:
	static Wind* create(ValueMap* initProperties, Size startSize, Vec2 startSpeed);

protected:
	Wind(ValueMap* initProperties, Size startSize, Vec2 startSpeed);
	~Wind();

private:
	void registerHackables();

	void update(float) override;

	HackableData * windDataSpeedY;
	ParticleSystem * windParticles;
	Vec2 windSpeed;
};
