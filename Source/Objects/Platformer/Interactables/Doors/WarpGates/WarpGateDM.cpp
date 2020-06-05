#include "WarpGateDM.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateDM::MapKey = "warp-gate-dm";

WarpGateDM* WarpGateDM::create(ValueMap& properties)
{
	WarpGateDM* instance = new WarpGateDM(properties);

	instance->autorelease();

	return instance;
}

WarpGateDM::WarpGateDM(ValueMap& properties) : super(properties)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalWind, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->edgeParticles->start();
	this->portalParticles->start();

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateDM::~WarpGateDM()
{
}

void WarpGateDM::onEnter()
{
	super::onEnter();
}

void WarpGateDM::initializePositions()
{
	super::initializePositions();
}

void WarpGateDM::initializeListeners()
{
	super::initializeListeners();
}

void WarpGateDM::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WarpGateDM::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
