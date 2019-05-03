#include "PointerTraceEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string PointerTraceEvents::EventEntityMoved = "EVENT_PTRACE_ENTITY_MOVED";
const std::string PointerTraceEvents::EventRequestMovement = "EVENT_PTRACE_REQUEST_MOVEMENT";
const std::string PointerTraceEvents::EventResumeMovement = "EVENT_PTRACE_RESUME_MOVEMENT";
const std::string PointerTraceEvents::EventInitializeRegisters = "EVENT_PTRACE_INITIALIZE_REGISTERS";

void PointerTraceEvents::TriggerEntityMoved(PointerTraceEntityMovedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PointerTraceEvents::EventEntityMoved,
		&args
	);
}

void PointerTraceEvents::TriggerRequestMovement(PointerTraceRequestMovementArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PointerTraceEvents::EventRequestMovement,
		&args
	);
}

void PointerTraceEvents::TriggerResumeMovement(PointerTraceRequestMovementArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PointerTraceEvents::EventResumeMovement,
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
