#include "EcxPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::vector<std::string> EcxPtrInitializer::MapKeyBases = {
	"[ecx+%d]",
	"[ecx + %d]",
	"[ecx +%d]",
	"[ecx+ %d]",
};
const std::string EcxPtrInitializer::MapKey = "[ecx]";

EcxPtrInitializer* EcxPtrInitializer::create(ValueMap& properties)
{
	EcxPtrInitializer* instance = new EcxPtrInitializer(properties);

	instance->autorelease();

	return instance;
}

EcxPtrInitializer::EcxPtrInitializer(ValueMap& properties) : super(properties)
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
