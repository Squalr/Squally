#include "EsiPtrJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEsi.h"
#include "Strings/PointerTrace/Assembly/RegisterRsi.h"

using namespace cocos2d;

const std::string EsiPtrJmp::MapKeyEsiPtrJmp = "esi-ptr-jmp";

EsiPtrJmp* EsiPtrJmp::create(ValueMap& initProperties)
{
	EsiPtrJmp* instance = new EsiPtrJmp(initProperties);

	instance->autorelease();

	return instance;
}

EsiPtrJmp::EsiPtrJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EsiPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEsi::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRsi::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EsiPtrJmp::~EsiPtrJmp()
{
}

void EsiPtrJmp::onEnter()
{
	super::onEnter();
}

void EsiPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EsiPtrJmp::getJumpDestination()
{
	int destination = 0;
	int address = RegisterState::getRegisterEsi() + this->getOffset();

	PointerTraceEvents::TriggerReadValue(PointerTraceEvents::PointerTraceReadArgs(address, [&](int readValue)
	{
		destination = readValue;
	}));

	return destination;
}
