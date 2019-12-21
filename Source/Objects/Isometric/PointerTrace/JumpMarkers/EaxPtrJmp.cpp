#include "EaxPtrJmp.h"

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

const std::string EaxPtrJmp::MapKeyEaxPtrJmp = "[eax]-jmp";

EaxPtrJmp* EaxPtrJmp::create(ValueMap& properties)
{
	EaxPtrJmp* instance = new EaxPtrJmp(properties);

	instance->autorelease();

	return instance;
}

EaxPtrJmp::EaxPtrJmp(ValueMap& properties) : super(properties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEax::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRax::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EaxPtrJmp::~EaxPtrJmp()
{
}

void EaxPtrJmp::onEnter()
{
	super::onEnter();
}

void EaxPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EaxPtrJmp::getJumpDestination()
{
	int destination = 0;
	int address = RegisterState::getRegisterEax() + this->getOffset();

	PointerTraceEvents::TriggerReadValue(PointerTraceEvents::PointerTraceReadArgs(address, [&](int readValue)
	{
		destination = readValue;
	}));

	return destination;
}
