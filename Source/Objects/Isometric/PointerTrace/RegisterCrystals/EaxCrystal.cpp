#include "EaxCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string EaxCrystal::MapKeyEaxCrystal = "eax-crystal";

EaxCrystal* EaxCrystal::create(ValueMap& initProperties)
{
	EaxCrystal* instance = new EaxCrystal(initProperties);

	instance->autorelease();

	return instance;
}

EaxCrystal::EaxCrystal(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->shadow = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_Shadow);
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxCrystal);

	this->addChild(this->shadow);
	this->addChild(this->crystal);
}

EaxCrystal::~EaxCrystal()
{
}

void EaxCrystal::onEnter()
{
	super::onEnter();

	this->crystal->runAction(RepeatForever::create(
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

void EaxCrystal::initializePositions()
{
	super::initializePositions();

	this->crystal->setPosition(Vec2(0.0f, 96.0f));
}
