#include "DarkPortal.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DarkPortal::MapKeyDarkPortal = "dark-portal";

DarkPortal* DarkPortal::create(ValueMap& properties)
{
	DarkPortal* instance = new DarkPortal(properties);

	instance->autorelease();

	return instance;
}

DarkPortal::DarkPortal(ValueMap& properties) : super(properties, 96.0f, Color4B::BLACK)
{
	this->portalParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalSand);

	this->portalEffectNode->addChild(this->portalParticles);
}

DarkPortal::~DarkPortal()
{
}

void DarkPortal::onEnter()
{
	super::onEnter();
}

void DarkPortal::initializePositions()
{
	super::initializePositions();
}

void DarkPortal::initializeListeners()
{
	super::initializeListeners();
}
