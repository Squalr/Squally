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

EaxCrystal::EaxCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxCrystal);

	this->crystalNode->addChild(this->crystal);
}

EaxCrystal::~EaxCrystal()
{
}

void EaxCrystal::onEnter()
{
	super::onEnter();
}

void EaxCrystal::initializePositions()
{
	super::initializePositions();
}
