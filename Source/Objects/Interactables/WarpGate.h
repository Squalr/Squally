#pragma once
#include "cocos2d.h"
#include "Objects/Collision/CollisionObject.h"

using namespace cocos2d;

class WarpGate : public CollisionObject
{
public:
	static WarpGate* create();

	void open();
	void close();

protected:
	WarpGate();
	~WarpGate();

private:
	void registerHackables();

	Sprite * gateOpen;
	Sprite * gateClosed;
	Sprite * gateClosedLights;
	Node * gateClosedLightsNode;
	ParticleSystem * gateParticles;
	ParticleSystem* sparkParticles;
	ParticleSystem* sparkParticlesBack;
	bool isOpen;
};
