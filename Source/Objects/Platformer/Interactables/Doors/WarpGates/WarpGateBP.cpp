#include "WarpGateBP.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateBP::MapKey = "warp-gate-bp";

WarpGateBP* WarpGateBP::create(ValueMap& properties)
{
	WarpGateBP* instance = new WarpGateBP(properties);

	instance->autorelease();

	return instance;
}

WarpGateBP::WarpGateBP(ValueMap& properties) : super(properties)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalFrost, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->edgeParticles->start();
	this->portalParticles->start();

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateBP::~WarpGateBP()
{
}

void WarpGateBP::onEnter()
{
	super::onEnter();
}

void WarpGateBP::initializePositions()
{
	super::initializePositions();
}

void WarpGateBP::initializeListeners()
{
	super::initializeListeners();
}

void WarpGateBP::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WarpGateBP::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
