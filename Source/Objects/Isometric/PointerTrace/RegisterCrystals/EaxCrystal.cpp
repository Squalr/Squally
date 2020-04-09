#include "EaxCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EaxCrystal::MapKey = "eax-crystal";

EaxCrystal* EaxCrystal::create(ValueMap& properties)
{
	EaxCrystal* instance = new EaxCrystal(properties);

	instance->autorelease();

	return instance;
}

EaxCrystal::EaxCrystal(ValueMap& properties) : super(properties)
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
