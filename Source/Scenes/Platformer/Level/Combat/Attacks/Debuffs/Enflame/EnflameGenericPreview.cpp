#include "EnflameGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

EnflameGenericPreview* EnflameGenericPreview::create()
{
	EnflameGenericPreview* instance = new EnflameGenericPreview();

	instance->autorelease();

	return instance;
}

EnflameGenericPreview::EnflameGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

EnflameGenericPreview::~EnflameGenericPreview()
{
}

HackablePreview* EnflameGenericPreview::clone()
{
	return EnflameGenericPreview::create();
}

void EnflameGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void EnflameGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
