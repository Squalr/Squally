#include "PointerTraceEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string PointerTraceEvents::EventInitializeRegisters = "EVENT_INITIALIZE_REGISTERS";

void PointerTraceEvents::TriggerInitializeRegisters(PointerTraceInitializeRegistersArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PointerTraceEvents::EventInitializeRegisters,
		&args
	);
}
