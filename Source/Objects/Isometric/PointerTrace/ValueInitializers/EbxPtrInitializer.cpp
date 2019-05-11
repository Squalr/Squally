#include "EbxPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EbxPtrInitializer::MapKeyEbxPtrInitializerRegex = "\\[ebx( ?(\\+|\\-) ?[0-9]+)?\\]";

EbxPtrInitializer* EbxPtrInitializer::create(ValueMap& initProperties)
{
	EbxPtrInitializer* instance = new EbxPtrInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EbxPtrInitializer::EbxPtrInitializer(ValueMap& initProperties) : super(initProperties)
{
}

EbxPtrInitializer::~EbxPtrInitializer()
{
}

void EbxPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEbx() + this->offset, gridIndex));
}
