#include "EcxCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string EcxCrystal::MapKeyEcxCrystal = "ecx-crystal";

EcxCrystal* EcxCrystal::create(ValueMap& initProperties)
{
	EcxCrystal* instance = new EcxCrystal(initProperties);

	instance->autorelease();

	return instance;
}

EcxCrystal::EcxCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EcxCrystal);

	this->crystalNode->addChild(this->crystal);
}

EcxCrystal::~EcxCrystal()
{
}

void EcxCrystal::onEnter()
{
	super::onEnter();
}

void EcxCrystal::initializePositions()
{
	super::initializePositions();
}

void EcxCrystal::updateRegister(int value)
{
	RegisterState::setRegisterEcx(value);
}

