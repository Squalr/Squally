#include "PullyHorizontal.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string PullyHorizontal::MapKey = "pully-horizontal";

PullyHorizontal* PullyHorizontal::create(ValueMap& properties)
{
	PullyHorizontal* instance = new PullyHorizontal(properties);

	instance->autorelease();

	return instance;
}

PullyHorizontal::PullyHorizontal(ValueMap& properties) : super(properties)
{
	bool isYellow = GameUtils::getKeyOrDefault(this->properties, GameObject::PropertyColor, Value("")).asString() == "yellow";
	this->wheelLeft = Sprite::create(isYellow ? ObjectResources::Decor_Pullies_WheelLight : ObjectResources::Decor_Pullies_WheelDark);
	this->wheelRight = Sprite::create(isYellow ? ObjectResources::Decor_Pullies_WheelLight : ObjectResources::Decor_Pullies_WheelDark);
	this->rope = SmartAnimationSequenceNode::create(ObjectResources::Decor_Pullies_PullyHorizontal_0000);

	this->addChild(this->rope);
	this->addChild(this->wheelLeft);
	this->addChild(this->wheelRight);
}

PullyHorizontal::~PullyHorizontal()
{
}

void PullyHorizontal::onEnter()
{
	super::onEnter();

	this->rope->playAnimationRepeat(ObjectResources::Decor_Pullies_PullyHorizontal_0000, 0.15f);
	this->wheelLeft->runAction(RepeatForever::create(RotateBy::create(5.0f, 360.0f)));
	this->wheelRight->runAction(RepeatForever::create(RotateBy::create(5.0f, 360.0f)));
}

void PullyHorizontal::initializePositions()
{
	super::initializePositions();

	this->rope->setPosition(Vec2(0.0f, 0.0f));
	this->wheelLeft->setPosition(Vec2(-144.0f, 11.0f));
	this->wheelRight->setPosition(Vec2(144.0f, 11.0f));
}
