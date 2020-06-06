#include "WarpGateDH.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateDH::MapKey = "warp-gate-dh";

WarpGateDH* WarpGateDH::create(ValueMap& properties)
{
	WarpGateDH* instance = new WarpGateDH(properties);

	instance->autorelease();

	return instance;
}

WarpGateDH::WarpGateDH(ValueMap& properties) : super(properties)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalFire, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->edgeParticles->start();
	this->portalParticles->start();

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateDH::~WarpGateDH()
{
}

void WarpGateDH::onEnter()
{
	super::onEnter();
	
	this->edgeParticles->start();
	this->portalParticles->start();
}

void WarpGateDH::lock(bool animate)
{
	super::lock(animate);
	
	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WarpGateDH::unlock(bool animate)
{
	super::unlock(animate);
	
	this->edgeParticles->start();
	this->portalParticles->start();
}
