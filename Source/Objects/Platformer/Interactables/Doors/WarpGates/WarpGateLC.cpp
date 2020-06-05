#include "WarpGateLC.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateLC::MapKey = "warp-gate-lc";

WarpGateLC* WarpGateLC::create(ValueMap& properties)
{
	WarpGateLC* instance = new WarpGateLC(properties);

	instance->autorelease();

	return instance;
}

WarpGateLC::WarpGateLC(ValueMap& properties) : super(properties)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalSand, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->portalParticles->start();

	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateLC::~WarpGateLC()
{
}

void WarpGateLC::onEnter()
{
	super::onEnter();
}

void WarpGateLC::initializePositions()
{
	super::initializePositions();
}

void WarpGateLC::initializeListeners()
{
	super::initializeListeners();
}
