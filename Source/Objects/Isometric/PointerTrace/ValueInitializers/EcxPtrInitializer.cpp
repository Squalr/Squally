#include "EcxPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::vector<std::string> EcxPtrInitializer::MapKeyEcxPtrInitializerBases = {
	"[ecx+%d]",
	"[ecx + %d]",
	"[ecx +%d]",
	"[ecx+ %d]",
};
const std::string EcxPtrInitializer::MapKeyEcxPtrInitializer = "[ecx]";

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
