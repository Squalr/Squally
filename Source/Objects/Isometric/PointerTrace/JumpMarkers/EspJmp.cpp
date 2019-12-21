#include "EspJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EspJmp::MapKeyEspJmp = "esp-jmp";

EspJmp* EspJmp::create(ValueMap& properties)
{
	EspJmp* instance = new EspJmp(properties);

	instance->autorelease();

	return instance;
}

EspJmp::EspJmp(ValueMap& properties) : super(properties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EspJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEsp::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRsp::create();

	this->buildJmpString(registerString);

	this->markerNode->addChild(this->marker);
}

EspJmp::~EspJmp()
{
}

void EspJmp::onEnter()
{
	super::onEnter();
}

void EspJmp::initializePositions()
{
	super::initializePositions();
}

int EspJmp::getJumpDestination()
{
	return RegisterState::getRegisterEsp();
}
