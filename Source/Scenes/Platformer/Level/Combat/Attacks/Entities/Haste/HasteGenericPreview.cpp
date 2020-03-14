#include "HasteGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

HasteGenericPreview* HasteGenericPreview::create()
{
	HasteGenericPreview* instance = new HasteGenericPreview();

	instance->autorelease();

	return instance;
}

HasteGenericPreview::HasteGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

HasteGenericPreview::~HasteGenericPreview()
{
}

HackablePreview* HasteGenericPreview::clone()
{
	return HasteGenericPreview::create();
}

void HasteGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void HasteGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
