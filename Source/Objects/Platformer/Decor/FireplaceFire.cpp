#include "FireplaceFire.h"

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

const std::string FireplaceFire::MapKey = "fireplace-fire";

FireplaceFire* FireplaceFire::create(ValueMap& properties)
{
	FireplaceFire* instance = new FireplaceFire(properties);

	instance->autorelease();

	return instance;
}

FireplaceFire::FireplaceFire(ValueMap& properties) : super(properties)
{
	this->glow = Sprite::create(ObjectResources::Decor_Fireplace_FireplaceGlow);
	this->fire = SmartAnimationSequenceNode::create(FXResources::FlameSmall_FlameSmall_0000);
	this->isOn = false;
	this->isCulled = false;

	this->addChild(this->glow);
	this->addChild(this->fire);
}

FireplaceFire::~FireplaceFire()
{
}

void FireplaceFire::onEnter()
{
	super::onEnter();

	this->fire->playAnimationRepeat(FXResources::FlameSmall_FlameSmall_0000, 0.07f);

	this->glow->runAction(RepeatForever::create(Sequence::create(
		FadeTo::create(1.0f, 127),
		DelayTime::create(0.25f),
		FadeTo::create(1.0f, 255),
		DelayTime::create(0.25f),
		nullptr
	)));
}

void FireplaceFire::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 0.0f));
	this->glow->setPosition(Vec2(0.0f, -32.0f));
}
