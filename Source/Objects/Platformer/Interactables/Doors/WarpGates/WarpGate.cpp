#include "WarpGate.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGate::TagWarpGate = "warp-gate";

WarpGate::WarpGate(ValueMap& properties) : super(properties, Size(128.0f, 256.0f))
{
	this->contentNode = Node::create();
	this->portalClip = SmartClippingNode::create(this->contentNode, Size(256.0f, 512.0f));
	this->portalEffectNode = Node::create();
	this->doorFrame = Sprite::create(ObjectResources::Doors_WarpGate_WarpGateFrame);
	this->portalOpenSound = WorldSound::create(SoundResources::Platformer_Objects_Doors_Portals_Portal);

	this->addTag(WarpGate::TagWarpGate);

	this->contentNode->addChild(this->portalEffectNode);
	this->addChild(this->portalClip);
	this->addChild(this->doorFrame);
	this->addChild(this->portalOpenSound);
}

WarpGate::~WarpGate()
{
}

void WarpGate::onEnter()
{
	super::onEnter();
}

void WarpGate::initializePositions()
{
	super::initializePositions();

	this->portalClip->setPosition(Vec2(0.0f, -78.0f));
}

void WarpGate::initializeListeners()
{
	super::initializeListeners();
}

void WarpGate::closePortal(bool instant)
{
	this->disable();

	if (instant)
	{
		this->contentNode->setOpacity(0);
	}
	else
	{
		this->contentNode->runAction(FadeTo::create(0.5f, 0));
	}
}

void WarpGate::openPortal(bool instant)
{
	if (instant)
	{
		this->contentNode->setOpacity(255);
	}
	else
	{
		this->contentNode->runAction(FadeTo::create(0.5f, 255));
		this->portalOpenSound->play();
	}

	this->enable();
}
