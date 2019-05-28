#include "EbpPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EbpPtrInitializer::MapKeyEbpPtrInitializerRegex = "\\[ebp( ?(\\+|\\-) ?[0-9]+)?\\]";

EbpPtrInitializer* EbpPtrInitializer::create(ValueMap& initProperties)
{
	EbpPtrInitializer* instance = new EbpPtrInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EbpPtrInitializer::EbpPtrInitializer(ValueMap& initProperties) : super(initProperties)
{
}

EbpPtrInitializer::~EbpPtrInitializer()
{
}

void EbpPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEbp() + this->offset, gridIndex));
}
