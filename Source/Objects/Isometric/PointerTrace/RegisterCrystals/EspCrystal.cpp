#include "EspCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string EspCrystal::MapKeyEspCrystal = "esp-crystal";

EspCrystal* EspCrystal::create(ValueMap& initProperties)
{
	EspCrystal* instance = new EspCrystal(initProperties);

	instance->autorelease();

	return instance;
}

EspCrystal::EspCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EspCrystal);

	this->crystalNode->addChild(this->crystal);
}

EspCrystal::~EspCrystal()
{
}

void EspCrystal::onEnter()
{
	super::onEnter();
}

void EspCrystal::initializePositions()
{
	super::initializePositions();
}
