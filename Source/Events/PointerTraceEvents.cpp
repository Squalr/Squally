#include "PointerTraceEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string PointerTraceEvents::EventVictory = "EVENT_PTRACE_VICTORY";
const std::string PointerTraceEvents::EventEntityMoved = "EVENT_PTRACE_ENTITY_MOVED";
const std::string PointerTraceEvents::EventRequestMovement = "EVENT_PTRACE_REQUEST_MOVEMENT";
const std::string PointerTraceEvents::EventResumeMovement = "EVENT_PTRACE_RESUME_MOVEMENT";
const std::string PointerTraceEvents::EventUpdateRegister = "EVENT_PTRACE_UPDATE_REGISTER";

void PointerTraceEvents::TriggerVictory()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PointerTraceEvents::EventVictory
	);
}

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

void PointerTraceEvents::TriggerRegisterUpdated()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PointerTraceEvents::EventUpdateRegister
	);
}
