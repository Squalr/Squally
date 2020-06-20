#include "BrokenBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BrokenBladeGenericPreview* BrokenBladeGenericPreview::create()
{
	BrokenBladeGenericPreview* instance = new BrokenBladeGenericPreview();

	instance->autorelease();

	return instance;
}

BrokenBladeGenericPreview::BrokenBladeGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

BrokenBladeGenericPreview::~BrokenBladeGenericPreview()
{
}

HackablePreview* BrokenBladeGenericPreview::clone()
{
	return BrokenBladeGenericPreview::create();
}

void BrokenBladeGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void BrokenBladeGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
