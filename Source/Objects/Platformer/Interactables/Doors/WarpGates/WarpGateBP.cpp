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
	
	this->edgeParticles->start();
	this->portalParticles->start();
}

void WarpGateBP::lock(bool animate)
{
	super::lock(animate);
	
	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WarpGateBP::unlock(bool animate)
{
	super::unlock(animate);
	
	this->edgeParticles->start();
	this->portalParticles->start();
}
