#include "WarpGateUR.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateUR::MapKey = "warp-gate-ur";

WarpGateUR* WarpGateUR::create(ValueMap& properties)
{
	WarpGateUR* instance = new WarpGateUR(properties);

	instance->autorelease();

	return instance;
}

WarpGateUR::WarpGateUR(ValueMap& properties) : super(properties)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalWater, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->edgeParticles->start();
	this->portalParticles->start();

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateUR::~WarpGateUR()
{
}

void WarpGateUR::onEnter()
{
	super::onEnter();
}

void WarpGateUR::initializePositions()
{
	super::initializePositions();
}

void WarpGateUR::initializeListeners()
{
	super::initializeListeners();
}
