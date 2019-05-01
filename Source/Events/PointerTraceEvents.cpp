#include "PointerTraceEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string PointerTraceEvents::EventRequestMovement = "EVENT_REQUEST_MOVEMENT";
const std::string PointerTraceEvents::EventInitializeRegisters = "EVENT_INITIALIZE_REGISTERS";

void PointerTraceEvents::TriggerRequestMovement(PointerTraceRequestMovementArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PointerTraceEvents::EventRequestMovement,
		&args
	);
}

void PointerTraceEvents::TriggerInitializeRegisters(PointerTraceInitializeRegistersArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PointerTraceEvents::EventInitializeRegisters,
		&args
	);
}
