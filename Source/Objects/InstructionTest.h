#pragma once
#include "cocos2d.h"
#include "udis86.h"
#include "Collision/CollisionObject.h"

using namespace cocos2d;

class InstructionTest : public CollisionObject
{
public:
	static InstructionTest* create();

	void open();
	void close();

protected:
	InstructionTest();
	~InstructionTest();

private:

	Sprite * gateOpen;
	Sprite * gateClosed;
	Sprite * gateClosedLights;
	Node * gateClosedLightsNode;
	ParticleSystem * gateParticles;
	ParticleSystem* sparkParticles;
	ParticleSystem* sparkParticlesBack;

	bool isOpen;
};
