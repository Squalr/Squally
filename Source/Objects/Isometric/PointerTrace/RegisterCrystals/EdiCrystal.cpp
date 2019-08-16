#include "EdiCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEdi.h"
#include "Strings/PointerTrace/Assembly/RegisterRdi.h"

using namespace cocos2d;

const std::string EdiCrystal::MapKeyEdiCrystal = "edi-crystal";

EdiCrystal* EdiCrystal::create(ValueMap& properties)
{
	EdiCrystal* instance = new EdiCrystal(properties);

	instance->autorelease();

	return instance;
}

EdiCrystal::EdiCrystal(ValueMap& properties) : super(properties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdiCrystal);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEdi::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRdi::create();

	this->buildString(registerString);

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

int EdiCrystal::getRegisterValue()
{
	return RegisterState::getRegisterEdi();
}
