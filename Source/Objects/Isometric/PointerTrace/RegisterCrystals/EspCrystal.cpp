#include "EspCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEsp.h"
#include "Strings/PointerTrace/Assembly/RegisterRsp.h"

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
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEsp::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRsp::create();

	this->buildString(registerString);

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

void EspCrystal::updateRegister(int value)
{
	RegisterState::setRegisterEsp(value);
}

int EspCrystal::getRegisterValue()
{
	return RegisterState::getRegisterEsp();
}
