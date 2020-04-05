#include "TimeBombGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

TimeBombGenericPreview* TimeBombGenericPreview::create()
{
	TimeBombGenericPreview* instance = new TimeBombGenericPreview();

	instance->autorelease();

	return instance;
}

TimeBombGenericPreview::TimeBombGenericPreview()
{
	this->timeBomb = Sprite::create(ObjectResources::Traps_TimeBomb_BOMB);

	this->previewNode->addChild(this->timeBomb);
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
}

void TimeBombGenericPreview::initializePositions()
{
	super::initializePositions();
}
