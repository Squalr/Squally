#include "EcxCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EcxCrystal::MapKey = "ecx-crystal";

EcxCrystal* EcxCrystal::create(ValueMap& properties)
{
	EcxCrystal* instance = new EcxCrystal(properties);

	instance->autorelease();

	return instance;
}

EcxCrystal::EcxCrystal(ValueMap& properties) : super(properties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EcxCrystal);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEcx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRcx::create();

	this->buildString(registerString);

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

int EcxCrystal::getRegisterValue()
{
	return RegisterState::getRegisterEcx();
}
