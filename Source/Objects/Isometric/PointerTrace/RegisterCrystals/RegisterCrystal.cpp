#include "RegisterCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string RegisterCrystal::MapKeyRegisterValue = "value";
const std::string RegisterCrystal::MapKeyRegisterOffset = "offset";

RegisterCrystal::RegisterCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->shadow = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_Shadow);
	this->crystalNode = Node::create();

	this->value = GameUtils::getKeyOrDefault(initProperties, RegisterCrystal::MapKeyRegisterValue, Value(0)).asInt();
	this->offset = GameUtils::getKeyOrDefault(initProperties, RegisterCrystal::MapKeyRegisterOffset, Value(0)).asInt();

	this->addChild(this->shadow);
	this->addChild(this->crystalNode);
}

RegisterCrystal::~RegisterCrystal()
{
}

void RegisterCrystal::onEnter()
{
	super::onEnter();

	this->crystalNode->runAction(RepeatForever::create(
		Sequence::create(
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 128.0f))),
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 96.0f))),
			nullptr
		)
	));
	this->shadow->runAction(RepeatForever::create(
		Sequence::create(
			ScaleTo::create(4.0f, 0.75f),
			ScaleTo::create(4.0f, 1.0f),
			nullptr
		)
	));
}

void RegisterCrystal::initializePositions()
{
	super::initializePositions();

	this->crystalNode->setPosition(Vec2(0.0f, 96.0f));
}

int RegisterCrystal::getValue()
{
	return this->value;
}

int RegisterCrystal::getOffset()
{
	return this->offset;
}
