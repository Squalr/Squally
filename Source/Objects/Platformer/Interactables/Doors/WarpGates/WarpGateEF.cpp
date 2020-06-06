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

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateEF::~WarpGateEF()
{
}

void WarpGateEF::onEnter()
{
	super::onEnter();
	
	this->edgeParticles->start();
	this->portalParticles->start();
}

void WarpGateEF::lock(bool animate)
{
	super::lock(animate);
	
	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WarpGateEF::unlock(bool animate)
{
	super::unlock(animate);
	
	this->edgeParticles->start();
	this->portalParticles->start();
}
