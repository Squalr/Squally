#include "WindPortal.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WindPortal::MapKey = "wind-portal";

WindPortal* WindPortal::create(ValueMap& properties)
{
	WindPortal* instance = new WindPortal(properties);

	instance->autorelease();

	return instance;
}

WindPortal::WindPortal(ValueMap& properties) : super(properties, 96.0f, Color4B::GRAY)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalWind, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->edgeParticles->start();
	this->portalParticles->start();

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

void WindPortal::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WindPortal::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
