#include "WindPortal.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WindPortal::MapKeyWindPortal = "wind-portal";

WindPortal* WindPortal::create(ValueMap& properties)
{
	WindPortal* instance = new WindPortal(properties);

	instance->autorelease();

	return instance;
}

WindPortal::WindPortal(ValueMap& properties) : super(properties, 96.0f, Color4B::RED)
{
	this->portalParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalFire);
	this->edgeParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalEdge);

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

WindPortal::~WindPortal()
{
}

void WindPortal::onEnter()
{
	super::onEnter();
}

void WindPortal::initializePositions()
{
	super::initializePositions();
}

void WindPortal::initializeListeners()
{
	super::initializeListeners();
}
