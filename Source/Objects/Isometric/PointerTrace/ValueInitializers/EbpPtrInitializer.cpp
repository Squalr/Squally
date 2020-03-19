#include "EbpPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::vector<std::string> EbpPtrInitializer::MapKeyBases = {
	"[ebp+%d]",
	"[ebp + %d]",
	"[ebp +%d]",
	"[ebp+ %d]",
};
const std::string EbpPtrInitializer::MapKey = "[ebp]";

EbpPtrInitializer* EbpPtrInitializer::create(ValueMap& properties)
{
	EbpPtrInitializer* instance = new EbpPtrInitializer(properties);

	instance->autorelease();

	return instance;
}

EbpPtrInitializer::EbpPtrInitializer(ValueMap& properties) : super(properties)
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
