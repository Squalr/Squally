#include "ManaDrainGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ManaDrainGenericPreview* ManaDrainGenericPreview::create()
{
	ManaDrainGenericPreview* instance = new ManaDrainGenericPreview();

	instance->autorelease();

	return instance;
}

ManaDrainGenericPreview::ManaDrainGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

ManaDrainGenericPreview::~ManaDrainGenericPreview()
{
}

HackablePreview* ManaDrainGenericPreview::clone()
{
	return ManaDrainGenericPreview::create();
}

void ManaDrainGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::HealMP_Heal_0000, 0.05f, 1.5f);
}

void ManaDrainGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
