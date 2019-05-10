#include "EdiPtrJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEdi.h"
#include "Strings/PointerTrace/Assembly/RegisterRdi.h"

using namespace cocos2d;

const std::string EdiPtrJmp::MapKeyEdiPtrJmp = "[edi]-jmp";

EdiPtrJmp* EdiPtrJmp::create(ValueMap& initProperties)
{
	EdiPtrJmp* instance = new EdiPtrJmp(initProperties);

	instance->autorelease();

	return instance;
}

EdiPtrJmp::EdiPtrJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdiPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEdi::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRdi::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EdiPtrJmp::~EdiPtrJmp()
{
}

void EdiPtrJmp::onEnter()
{
	super::onEnter();
}

void EdiPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EdiPtrJmp::getJumpDestination()
{
	int destination = 0;
	int address = RegisterState::getRegisterEdi() + this->getOffset();

	PointerTraceEvents::TriggerReadValue(PointerTraceEvents::PointerTraceReadArgs(address, [&](int readValue)
	{
		destination = readValue;
	}));

	return destination;
}
