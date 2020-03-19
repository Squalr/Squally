#include "EbxPtrJmp.h"

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

const std::string EbxPtrJmp::MapKey = "[ebx]-jmp";

EbxPtrJmp* EbxPtrJmp::create(ValueMap& properties)
{
	EbxPtrJmp* instance = new EbxPtrJmp(properties);

	instance->autorelease();

	return instance;
}

EbxPtrJmp::EbxPtrJmp(ValueMap& properties) : super(properties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbxPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEbx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRbx::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EbxPtrJmp::~EbxPtrJmp()
{
}

void EbxPtrJmp::onEnter()
{
	super::onEnter();
}

void EbxPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EbxPtrJmp::getJumpDestination()
{
	int destination = 0;
	int address = RegisterState::getRegisterEbx() + this->getOffset();

	PointerTraceEvents::TriggerReadValue(PointerTraceEvents::PointerTraceReadArgs(address, [&](int readValue)
	{
		destination = readValue;
	}));

	return destination;
}
