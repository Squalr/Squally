#include "ReflectGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ReflectGenericPreview* ReflectGenericPreview::create()
{
	ReflectGenericPreview* instance = new ReflectGenericPreview();

	instance->autorelease();

	return instance;
}

ReflectGenericPreview::ReflectGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

ReflectGenericPreview::~ReflectGenericPreview()
{
}

HackablePreview* ReflectGenericPreview::clone()
{
	return ReflectGenericPreview::create();
}

void ReflectGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void ReflectGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
