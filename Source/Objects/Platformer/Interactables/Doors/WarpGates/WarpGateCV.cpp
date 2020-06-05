#include "WarpGateCV.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateCV::MapKey = "warp-gate-cv";

WarpGateCV* WarpGateCV::create(ValueMap& properties)
{
	WarpGateCV* instance = new WarpGateCV(properties);

	instance->autorelease();

	return instance;
}

WarpGateCV::WarpGateCV(ValueMap& properties) : super(properties)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalSand, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->portalParticles->start();

	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateCV::~WarpGateCV()
{
}

void WarpGateCV::onEnter()
{
	super::onEnter();
}

void WarpGateCV::initializePositions()
{
	super::initializePositions();
}

void WarpGateCV::initializeListeners()
{
	super::initializeListeners();
}
