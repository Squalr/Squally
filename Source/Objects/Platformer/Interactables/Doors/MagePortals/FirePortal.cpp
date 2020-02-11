#include "FirePortal.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

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
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalFire, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));

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

void FirePortal::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void FirePortal::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
