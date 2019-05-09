#include "EspPtrJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEsp.h"
#include "Strings/PointerTrace/Assembly/RegisterRsp.h"

using namespace cocos2d;

const std::string EspPtrJmp::MapKeyEspPtrJmp = "esp-ptr-jmp";

EspPtrJmp* EspPtrJmp::create(ValueMap& initProperties)
{
	EspPtrJmp* instance = new EspPtrJmp(initProperties);

	instance->autorelease();

	return instance;
}

EspPtrJmp::EspPtrJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EspPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEsp::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRsp::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EspPtrJmp::~EspPtrJmp()
{
}

void EspPtrJmp::onEnter()
{
	super::onEnter();
}

void EspPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EspPtrJmp::getJumpDestination()
{
	int destination = 0;
	int address = RegisterState::getRegisterEsp() + this->getOffset();

	PointerTraceEvents::TriggerReadValue(PointerTraceEvents::PointerTraceReadArgs(address, [&](int readValue)
	{
		destination = readValue;
	}));

	return destination;
}
