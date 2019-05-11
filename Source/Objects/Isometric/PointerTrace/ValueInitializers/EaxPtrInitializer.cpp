#include "EaxPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EaxPtrInitializer::MapKeyEaxPtrInitializerRegex = "\\[eax( ?(\\+|\\-) ?[0-9]+)?\\]";

EaxPtrInitializer* EaxPtrInitializer::create(ValueMap& initProperties)
{
	EaxPtrInitializer* instance = new EaxPtrInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EaxPtrInitializer::EaxPtrInitializer(ValueMap& initProperties) : super(initProperties)
{
}

EaxPtrInitializer::~EaxPtrInitializer()
{
}

void EaxPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEax() + this->offset, gridIndex));
}
