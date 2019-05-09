#include "EsiPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EsiPtrInitializer::MapKeyEsiPtrInitializer = "[esi]";

EsiPtrInitializer* EsiPtrInitializer::create(ValueMap& initProperties)
{
	EsiPtrInitializer* instance = new EsiPtrInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EsiPtrInitializer::EsiPtrInitializer(ValueMap& initProperties) : super(initProperties)
{
}

EsiPtrInitializer::~EsiPtrInitializer()
{
}

void EsiPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEsi(), gridIndex));
}
