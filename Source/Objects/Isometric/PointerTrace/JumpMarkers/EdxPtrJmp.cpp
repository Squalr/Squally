#include "EdxPtrJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEdx.h"
#include "Strings/PointerTrace/Assembly/RegisterRdx.h"

using namespace cocos2d;

const std::string EdxPtrJmp::MapKeyEdxPtrJmp = "edx-ptr-jmp";

EdxPtrJmp* EdxPtrJmp::create(ValueMap& initProperties)
{
	EdxPtrJmp* instance = new EdxPtrJmp(initProperties);

	instance->autorelease();

	return instance;
}

EdxPtrJmp::EdxPtrJmp(ValueMap& initProperties) : super(initProperties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdxPtrJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEdx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRdx::create();

	this->buildJmpPtrString(registerString);

	this->markerNode->addChild(this->marker);
}

EdxPtrJmp::~EdxPtrJmp()
{
}

void EdxPtrJmp::onEnter()
{
	super::onEnter();
}

void EdxPtrJmp::initializePositions()
{
	super::initializePositions();
}

int EdxPtrJmp::getJumpDestination()
{
	int destination = 0;
	int address = RegisterState::getRegisterEdx() + this->getOffset();

	PointerTraceEvents::TriggerReadValue(PointerTraceEvents::PointerTraceReadArgs(address, [&](int readValue)
	{
		destination = readValue;
	}));

	return destination;
}
