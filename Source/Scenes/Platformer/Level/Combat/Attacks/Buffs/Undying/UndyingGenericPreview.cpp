#include "UndyingGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

UndyingGenericPreview* UndyingGenericPreview::create()
{
	UndyingGenericPreview* instance = new UndyingGenericPreview();

	instance->autorelease();

	return instance;
}

UndyingGenericPreview::UndyingGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

UndyingGenericPreview::~UndyingGenericPreview()
{
}

HackablePreview* UndyingGenericPreview::clone()
{
	return UndyingGenericPreview::create();
}

void UndyingGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void UndyingGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
