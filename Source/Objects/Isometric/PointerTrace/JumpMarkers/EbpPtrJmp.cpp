#include "EbpPtrJmp.h"

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

const std::string EbpPtrJmp::MapKey = "[ebp]-jmp";

EbpPtrJmp* EbpPtrJmp::create(ValueMap& properties)
{
	EbpPtrJmp* instance = new EbpPtrJmp(properties);

	instance->autorelease();

	return instance;
}

EbpPtrJmp::EbpPtrJmp(ValueMap& properties) : super(properties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbpPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEbp::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRbp::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EbpPtrJmp::~EbpPtrJmp()
{
}

void EbpPtrJmp::onEnter()
{
	super::onEnter();
}

void EbpPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EbpPtrJmp::getJumpDestination()
{
	int destination = 0;
	int address = RegisterState::getRegisterEbp() + this->getOffset();

	PointerTraceEvents::TriggerReadValue(PointerTraceEvents::PointerTraceReadArgs(address, [&](int readValue)
	{
		destination = readValue;
	}));

	return destination;
}
