#include "MagePortal.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

MagePortal::MagePortal(ValueMap& properties, float portalRadius, Color4B portalBaseColor) : super(properties, Size(128.0f, 256.0f))
{
	this->contentNode = Node::create();
	this->portalBase = SmartClippingNode::create(this->contentNode, portalRadius);
	this->portalEffectNode = Node::create();
	this->background = DrawNode::create();
	this->edge = DrawNode::create();
	this->portalOpenSound = WorldSound::create(SoundResources::Platformer_Doors_Portals_Portal);

	this->background->drawSolidCircle(Vec2::ZERO, portalRadius, 0.0f, 32, Color4F(portalBaseColor));
	
	this->portalBase->setScaleX(0.5f);
	this->drawEdge(Color4F::BLACK, this->edge, portalRadius, 8);

	this->contentNode->addChild(this->background);
	this->contentNode->addChild(this->portalEffectNode);
	this->contentNode->addChild(this->edge);
	this->addChild(this->portalBase);
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
}

void MagePortal::drawEdge(cocos2d::Color4F edgeColor, cocos2d::DrawNode* drawNode, float radius, int thickness)
{
	for (int index = 0; index < thickness; index++)
	{
		drawNode->drawCircle(Vec2::ZERO, radius, 0.0f, 32, false, Color4F::BLACK);
		radius -= 1.0f;
	}
}
