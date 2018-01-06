#pragma once
#include "cocos2d.h"
#include "Collision/CollisionObject.h"
#include "GUI/Components/FloatingSprite.h"

using namespace cocos2d;

class Monitor : public CollisionObject
{
public:
	static Monitor* create();

protected:
	Monitor();
	~Monitor();

private:

	FloatingSprite * monitorSprite;
	ParticleSystem * monitorParticles;
	ParticleSystem * monitorParticlesBack;
};
