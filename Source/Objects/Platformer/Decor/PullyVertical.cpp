#include "PullyVertical.h"

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

const std::string PullyVertical::MapKey = "pully-vertical";

PullyVertical* PullyVertical::create(ValueMap& properties)
{
	PullyVertical* instance = new PullyVertical(properties);

	instance->autorelease();

	return instance;
}

PullyVertical::PullyVertical(ValueMap& properties) : super(properties)
{
	bool isYellow = GameUtils::getKeyOrDefault(this->properties, GameObject::PropertyColor, Value("")).asString() == "yellow";
	this->wheel = Sprite::create(isYellow ? ObjectResources::Decor_Pullies_WheelLight : ObjectResources::Decor_Pullies_WheelDark);
	this->rope = SmartAnimationSequenceNode::create(ObjectResources::Decor_Pullies_PullyVertical_0000);

	this->addChild(this->rope);
	this->addChild(this->wheel);
}

PullyVertical::~PullyVertical()
{
}

void PullyVertical::onEnter()
{
	super::onEnter();

	this->rope->playAnimationRepeat(ObjectResources::Decor_Pullies_PullyVertical_0000, 0.15f);
	this->wheel->runAction(RepeatForever::create(RotateBy::create(5.0f, 360.0f)));
}

void PullyVertical::initializePositions()
{
	super::initializePositions();

	this->rope->setPosition(Vec2(0.0f, 0.0f));
	this->wheel->setPosition(Vec2(1.0f, -116.0f));
}
