#include "EspPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EspPtrInitializer::MapKeyEspPtrInitializer = "[esp]";

EspPtrInitializer* EspPtrInitializer::create(ValueMap& initProperties)
{
	EspPtrInitializer* instance = new EspPtrInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EspPtrInitializer::EspPtrInitializer(ValueMap& initProperties) : super(initProperties)
{
}

EspPtrInitializer::~EspPtrInitializer()
{
}

void EspPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEsp(), gridIndex));
}
