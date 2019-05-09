#include "EdiPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EdiPtrInitializer::MapKeyEdiPtrInitializer = "[edi]";

EdiPtrInitializer* EdiPtrInitializer::create(ValueMap& initProperties)
{
	EdiPtrInitializer* instance = new EdiPtrInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EdiPtrInitializer::EdiPtrInitializer(ValueMap& initProperties) : super(initProperties)
{
}

EdiPtrInitializer::~EdiPtrInitializer()
{
}

void EdiPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEdi(), gridIndex));
}
