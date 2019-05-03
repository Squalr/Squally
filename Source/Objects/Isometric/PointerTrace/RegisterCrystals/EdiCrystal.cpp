#include "EdiCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string EdiCrystal::MapKeyEdiCrystal = "edi-crystal";

EdiCrystal* EdiCrystal::create(ValueMap& initProperties)
{
	EdiCrystal* instance = new EdiCrystal(initProperties);

	instance->autorelease();

	return instance;
}

EdiCrystal::EdiCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdiCrystal);

	this->crystalNode->addChild(this->crystal);
}

EdiCrystal::~EdiCrystal()
{
}

void EdiCrystal::onEnter()
{
	super::onEnter();
}

void EdiCrystal::initializePositions()
{
	super::initializePositions();
}

void EdiCrystal::updateRegister(int value)
{
	RegisterState::setRegisterEdi(value);
}
