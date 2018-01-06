#pragma once
#include "cocos2d.h"
#include "Collision/CollisionObject.h"
#include "GUI/Components/FloatingSprite.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class Monitor : public CollisionObject
{
public:
	static Monitor* create();

protected:
	Monitor();
	~Monitor();

private:

	MenuSprite * monitorSprite;
	FloatingSprite * monitorSpriteFloating;
	ParticleSystem * monitorParticles;
	ParticleSystem * monitorParticlesBack;
};
