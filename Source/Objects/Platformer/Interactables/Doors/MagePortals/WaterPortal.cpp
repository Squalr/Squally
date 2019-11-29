#include "WaterPortal.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WaterPortal::MapKeyWaterPortal = "water-portal";

WaterPortal* WaterPortal::create(ValueMap& properties)
{
	WaterPortal* instance = new WaterPortal(properties);

	instance->autorelease();

	return instance;
}

WaterPortal::WaterPortal(ValueMap& properties) : super(properties, 96.0f, Color4B::BLUE)
{
	this->portalParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalWater);
	this->edgeParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalEdge);

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
