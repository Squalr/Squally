#include "EbpCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEbp.h"
#include "Strings/PointerTrace/Assembly/RegisterRbp.h"

using namespace cocos2d;

const std::string EbpCrystal::MapKeyEbpCrystal = "ebp-crystal";

EbpCrystal* EbpCrystal::create(ValueMap& initProperties)
{
	EbpCrystal* instance = new EbpCrystal(initProperties);

	instance->autorelease();

	return instance;
}

EbpCrystal::EbpCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbpCrystal);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEbp::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRbp::create();

	this->buildString(registerString);

	this->crystalNode->addChild(this->crystal);
}

EbpCrystal::~EbpCrystal()
{
}

void EbpCrystal::onEnter()
{
	super::onEnter();
}

void EbpCrystal::initializePositions()
{
	super::initializePositions();
}

void EbpCrystal::updateRegister(int value)
{
	RegisterState::setRegisterEbp(value);
}

int EbpCrystal::getRegisterValue()
{
	return RegisterState::getRegisterEbp();
}
