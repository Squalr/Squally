#include "HotPotatoGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

HotPotatoGenericPreview* HotPotatoGenericPreview::create()
{
	HotPotatoGenericPreview* instance = new HotPotatoGenericPreview();

	instance->autorelease();

	return instance;
}

HotPotatoGenericPreview::HotPotatoGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

HotPotatoGenericPreview::~HotPotatoGenericPreview()
{
}

HackablePreview* HotPotatoGenericPreview::clone()
{
	return HotPotatoGenericPreview::create();
}

void HotPotatoGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void HotPotatoGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
