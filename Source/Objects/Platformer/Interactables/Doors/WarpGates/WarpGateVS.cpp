#include "WarpGateVS.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateVS::MapKey = "warp-gate-vs";

WarpGateVS* WarpGateVS::create(ValueMap& properties)
{
	WarpGateVS* instance = new WarpGateVS(properties);

	instance->autorelease();

	return instance;
}

WarpGateVS::WarpGateVS(ValueMap& properties) : super(properties)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalVoid, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->portalParticles->start();

	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateVS::~WarpGateVS()
{
}

void WarpGateVS::onEnter()
{
	super::onEnter();
}

void WarpGateVS::initializePositions()
{
	super::initializePositions();
}

void WarpGateVS::initializeListeners()
{
	super::initializeListeners();
}

void WarpGateVS::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WarpGateVS::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
