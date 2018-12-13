#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableObject.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"

using namespace cocos2d;

class WarpGate : public HackableObject
{
public:
	static WarpGate* create(ValueMap* initProperties);

	void open();
	void close();

	static const std::string MapKeyWarpGate;

protected:
	WarpGate(ValueMap* initProperties);
	~WarpGate();

	Vec2 getButtonOffset() override;

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
