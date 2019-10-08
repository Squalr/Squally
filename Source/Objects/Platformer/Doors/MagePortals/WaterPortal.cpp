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

WaterPortal::WaterPortal(ValueMap& properties) : super(properties)
{
	this->background = DrawNode::create();
	this->portalParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalFire);
	this->edge = DrawNode::create();

	this->background->drawSolidCircle(Vec2::ZERO, 96.0f, 0.0f, 32, Color4F::RED);
	this->drawEdge(Color4F::BLACK, this->edge, 96.0f, 6);

	this->contentNode->addChild(this->background);
	this->contentNode->addChild(this->portalParticles);
	this->contentNode->addChild(this->edge);
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
