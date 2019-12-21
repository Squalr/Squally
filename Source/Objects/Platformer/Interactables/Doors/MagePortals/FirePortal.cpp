#include "FirePortal.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string FirePortal::MapKeyFirePortal = "fire-portal";

FirePortal* FirePortal::create(ValueMap& properties)
{
	FirePortal* instance = new FirePortal(properties);

	instance->autorelease();

	return instance;
}

FirePortal::FirePortal(ValueMap& properties) : super(properties, 96.0f, Color4B::RED)
{
	this->portalParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalFire);
	this->edgeParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalEdge);

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

FirePortal::~FirePortal()
{
}

void FirePortal::onEnter()
{
	super::onEnter();
}

void FirePortal::initializePositions()
{
	super::initializePositions();
}

void FirePortal::initializeListeners()
{
	super::initializeListeners();
}
