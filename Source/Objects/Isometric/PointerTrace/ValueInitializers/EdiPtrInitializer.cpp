#include "EdiPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::vector<std::string> EdiPtrInitializer::MapKeyBases = {
	"[edi+%d]",
	"[edi + %d]",
	"[edi +%d]",
	"[edi+ %d]",
};
const std::string EdiPtrInitializer::MapKey = "[edi]";

EdiPtrInitializer* EdiPtrInitializer::create(ValueMap& properties)
{
	EdiPtrInitializer* instance = new EdiPtrInitializer(properties);

	instance->autorelease();

	return instance;
}

EdiPtrInitializer::EdiPtrInitializer(ValueMap& properties) : super(properties)
{
}

EdiPtrInitializer::~EdiPtrInitializer()
{
}

void EdiPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEdi() + this->offset, gridIndex));
}
