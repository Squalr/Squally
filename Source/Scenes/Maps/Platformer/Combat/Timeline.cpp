#include "Timeline.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/UI/Controls/CProgressBar.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/UIResources.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const float Timeline::CastPercentage = 0.2f;

Timeline* Timeline::create()
{
	Timeline* instance = new Timeline();

	instance->autorelease();

	return instance;
}

Timeline::Timeline()
{
	this->swordFill = CProgressBar::create(Sprite::create(UIResources::Combat_SwordFillRed), Sprite::create(UIResources::Combat_SwordFill), Vec2::ZERO);
	this->swordTop = Sprite::create(UIResources::Combat_SwordTop);

	this->swordFill->setProgress(1.0f - Timeline::CastPercentage);

	this->addChild(this->swordFill);
	this->addChild(this->swordTop);
}

void Timeline::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Timeline::initializePositions()
{
	super::initializePositions();

	const float fillOffsetX = 48.0f;

	this->swordTop->setPositionX(-fillOffsetX);
}

void Timeline::initializeListeners()
{
	super::initializeListeners();
}

void Timeline::update(float dt)
{
	super::update(dt);
}

