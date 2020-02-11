#include "DarkPortal.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

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
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalSand, SmartParticles::CullInfo(Size(96.0f, 96.0f)));

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

void DarkPortal::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void DarkPortal::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
