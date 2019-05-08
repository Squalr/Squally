#include "EaxCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Strings/PointerTrace/Assembly/RegisterEax.h"
#include "Strings/PointerTrace/Assembly/RegisterRax.h"

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
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEax::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRax::create();

	this->buildString(registerString);

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

void EaxCrystal::updateRegister(int value)
{
	RegisterState::setRegisterEax(value);
}

int EaxCrystal::getRegisterValue()
{
	return RegisterState::getRegisterEax();
}
