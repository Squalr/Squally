#include "EnrageGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

EnrageGenericPreview* EnrageGenericPreview::create()
{
	EnrageGenericPreview* instance = new EnrageGenericPreview();

	instance->autorelease();

	return instance;
}

EnrageGenericPreview::EnrageGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

EnrageGenericPreview::~EnrageGenericPreview()
{
}

HackablePreview* EnrageGenericPreview::clone()
{
	return EnrageGenericPreview::create();
}

void EnrageGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void EnrageGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
