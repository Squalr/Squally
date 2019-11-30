#include "EcxPtrJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EcxPtrJmp::MapKeyEcxPtrJmp = "[ecx]-jmp";

EcxPtrJmp* EcxPtrJmp::create(ValueMap& properties)
{
	EcxPtrJmp* instance = new EcxPtrJmp(properties);

	instance->autorelease();

	return instance;
}

EcxPtrJmp::EcxPtrJmp(ValueMap& properties) : super(properties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EcxPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEcx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRcx::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EcxPtrJmp::~EcxPtrJmp()
{
}

void EcxPtrJmp::onEnter()
{
	super::onEnter();
}

void EcxPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EcxPtrJmp::getJumpDestination()
{
	int destination = 0;
	int address = RegisterState::getRegisterEcx() + this->getOffset();

	PointerTraceEvents::TriggerReadValue(PointerTraceEvents::PointerTraceReadArgs(address, [&](int readValue)
	{
		destination = readValue;
	}));

	return destination;
}
