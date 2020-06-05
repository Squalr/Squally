#include "WarpGateEF.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateEF::MapKey = "warp-gate-ef";

WarpGateEF* WarpGateEF::create(ValueMap& properties)
{
	WarpGateEF* instance = new WarpGateEF(properties);

	instance->autorelease();

	return instance;
}

WarpGateEF::WarpGateEF(ValueMap& properties) : super(properties)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalNature, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalNatureEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->edgeParticles->start();
	this->portalParticles->start();

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateEF::~WarpGateEF()
{
}

void WarpGateEF::onEnter()
{
	super::onEnter();
}

void WarpGateEF::initializePositions()
{
	super::initializePositions();
}

void WarpGateEF::initializeListeners()
{
	super::initializeListeners();
}

void WarpGateEF::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WarpGateEF::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
