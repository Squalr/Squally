#include "WaterPortal.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WaterPortal::MapKey = "water-portal";

WaterPortal* WaterPortal::create(ValueMap& properties)
{
	WaterPortal* instance = new WaterPortal(properties);

	instance->autorelease();

	return instance;
}

WaterPortal::WaterPortal(ValueMap& properties) : super(properties, 96.0f, Color4B::BLUE)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalWater, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

WaterPortal::~WaterPortal()
{
}

void WaterPortal::onEnter()
{
	super::onEnter();
}

void WaterPortal::initializePositions()
{
	super::initializePositions();
}

void WaterPortal::initializeListeners()
{
	super::initializeListeners();
}

void WaterPortal::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WaterPortal::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
