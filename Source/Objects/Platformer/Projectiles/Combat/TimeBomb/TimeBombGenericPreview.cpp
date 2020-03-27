#include "TimeBombGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

TimeBombGenericPreview* TimeBombGenericPreview::create()
{
	TimeBombGenericPreview* instance = new TimeBombGenericPreview();

	instance->autorelease();

	return instance;
}

TimeBombGenericPreview::TimeBombGenericPreview()
{
	this->fireball = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);

	this->previewNode->addChild(this->fireball);
}

TimeBombGenericPreview::~TimeBombGenericPreview()
{
}

HackablePreview* TimeBombGenericPreview::clone()
{
	return TimeBombGenericPreview::create();
}

void TimeBombGenericPreview::onEnter()
{
	super::onEnter();

	this->fireball->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.085f);
}

void TimeBombGenericPreview::initializePositions()
{
	super::initializePositions();
}
