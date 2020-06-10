#include "WeaknessGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

WeaknessGenericPreview* WeaknessGenericPreview::create()
{
	WeaknessGenericPreview* instance = new WeaknessGenericPreview();

	instance->autorelease();

	return instance;
}

WeaknessGenericPreview::WeaknessGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

WeaknessGenericPreview::~WeaknessGenericPreview()
{
}

HackablePreview* WeaknessGenericPreview::clone()
{
	return WeaknessGenericPreview::create();
}

void WeaknessGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void WeaknessGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
