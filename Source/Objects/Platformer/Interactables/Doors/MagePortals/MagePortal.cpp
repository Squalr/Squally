#include "MagePortal.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Particles/SmartParticles.h"

#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"

#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string MagePortal::MapKey = "mage-portal";
const float MagePortal::PortalRadius = 96.0f;
const Color4B MagePortal::BaseColor = Color4B::BLUE;

MagePortal* MagePortal::create(ValueMap& properties)
{
	MagePortal* instance = new MagePortal(properties);

	instance->autorelease();

	return instance;
}

MagePortal::MagePortal(ValueMap& properties) : super(properties, Size(128.0f, 256.0f))
{
	this->portalContentNode = Node::create();
	this->portalBase = SmartClippingNode::create(this->portalContentNode, MagePortal::PortalRadius);
	this->portalEffectNode = Node::create();
	this->background = DrawNode::create();
	this->edge = DrawNode::create();
	this->portalOpenSound = WorldSound::create(SoundResources::Platformer_Objects_Doors_Portals_Portal);
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalFrost, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->edgeParticles->start();
	this->portalParticles->start();

	this->addTag(MagePortal::MapKey);

	this->background->drawSolidCircle(Vec2::ZERO, MagePortal::PortalRadius, 0.0f, 32, Color4F(MagePortal::BaseColor));
	
	this->portalBase->setScaleX(0.5f);
	this->drawEdge(Color4F::BLACK, this->edge, MagePortal::PortalRadius, 8);
	
	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
	this->portalContentNode->addChild(this->background);
	this->portalContentNode->addChild(this->portalEffectNode);
	this->portalContentNode->addChild(this->edge);
	this->contentNode->addChild(this->portalBase);
	this->addChild(this->portalOpenSound);
}

MagePortal::~MagePortal()
{
}

void MagePortal::onEnter()
{
	super::onEnter();
}

void MagePortal::initializePositions()
{
	super::initializePositions();
}

void MagePortal::initializeListeners()
{
	super::initializeListeners();
}

void MagePortal::closePortal(bool instant)
{
	this->disable();

	this->edgeParticles->stop();
	this->portalParticles->stop();

	if (instant)
	{
		this->setOpacity(0);
	}
	else
	{
		this->runAction(FadeTo::create(0.5f, 0));
	}
}

void MagePortal::openPortal(bool instant)
{
	if (instant)
	{
		this->setOpacity(255);
	}
	else
	{
		this->runAction(FadeTo::create(0.5f, 255));
		this->portalOpenSound->play();
	}

	this->enable();

	this->edgeParticles->start();
	this->portalParticles->start();
}

void MagePortal::drawEdge(cocos2d::Color4F edgeColor, cocos2d::DrawNode* drawNode, float radius, int thickness)
{
	for (int index = 0; index < thickness; index++)
	{
		drawNode->drawCircle(Vec2::ZERO, radius, 0.0f, 32, false, Color4F::BLACK);
		radius -= 1.0f;
	}
}
