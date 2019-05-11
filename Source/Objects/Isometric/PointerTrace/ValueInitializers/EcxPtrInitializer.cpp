#include "EcxPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EcxPtrInitializer::MapKeyEcxPtrInitializerRegex = "\\[ecx( ?(\\+|\\-) ?[0-9]+)?\\]";

EcxPtrInitializer* EcxPtrInitializer::create(ValueMap& initProperties)
{
	EcxPtrInitializer* instance = new EcxPtrInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EcxPtrInitializer::EcxPtrInitializer(ValueMap& initProperties) : super(initProperties)
{
}

EcxPtrInitializer::~EcxPtrInitializer()
{
}

void EcxPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEcx() + this->offset, gridIndex));	
}
