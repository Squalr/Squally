#include "MineLantern.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string MineLantern::MapKey = "mine-lantern";

MineLantern* MineLantern::create(ValueMap& properties)
{
	MineLantern* instance = new MineLantern(properties);

	instance->autorelease();

	return instance;
}

MineLantern::MineLantern(ValueMap& properties) : super(properties)
{
	this->lanternBack = Sprite::create(ObjectResources::Decor_MineLantern_LanternBack);
	this->glow = Sprite::create(ObjectResources::Decor_MineLantern_TorchGlow);
	this->fire = SmartAnimationSequenceNode::create(FXResources::TorchFire_TorchFire_0000);
	this->lantern = Sprite::create(ObjectResources::Decor_MineLantern_LanternFront);
	this->isOn = false;
	this->isCulled = false;

	this->setContentSize(Size(128.0f, 128.0f));

	this->addChild(this->lanternBack);
	this->addChild(this->glow);
	this->addChild(this->fire);
	this->addChild(this->lantern);
}

MineLantern::~MineLantern()
{
}

void MineLantern::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
	this->lanternOn();
	this->optimizationHideOffscreenMineLantern();
}

void MineLantern::initializePositions()
{
	super::initializePositions();

	// this->fire->setPosition(Vec2(0.0f, 0.0f));
	// this->glow->setPosition(Vec2(0.0f, 56.0f));
}

void MineLantern::update(float dt)
{
	super::update(dt);
	
	this->optimizationHideOffscreenMineLantern();
}

void MineLantern::lanternOn()
{
	if (this->isOn)
	{
		return;
	}

	this->isOn = true;

	this->optimizationHideOffscreenMineLantern();
}

void MineLantern::lanternOff()
{
	if (!this->isOn)
	{
		return;
	}

	this->isOn = false;

	this->updateMineLanternVisibility();
}

void MineLantern::updateMineLanternVisibility()
{
	this->glow->stopAllActions();
	this->fire->stopAnimation();

	if (this->isOn && !this->isCulled)
	{
		this->fire->playAnimationRepeat(FXResources::TorchFire_TorchFire_0000, 0.05f);

		this->glow->runAction(RepeatForever::create(Sequence::create(
			FadeTo::create(1.0f, 0),
			DelayTime::create(0.25f),
			FadeTo::create(1.0f, 255),
			DelayTime::create(0.25f),
			nullptr
		)));
	}
}

void MineLantern::optimizationHideOffscreenMineLantern()
{
	static const Size Padding = Size(128.0f, 128.0f);
	static const Rect CameraRect = Rect(Vec2::ZERO, Director::getInstance()->getVisibleSize());
	Rect thisRect = GameUtils::getScreenBounds(this, Padding);

	bool isNotOnScreen = !CameraRect.intersectsRect(thisRect);

	if (this->isCulled != isNotOnScreen)
	{
		this->isCulled = isNotOnScreen;

		this->updateMineLanternVisibility();
	}
}
