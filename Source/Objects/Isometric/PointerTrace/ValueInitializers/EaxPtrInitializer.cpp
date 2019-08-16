#include "EaxPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::vector<std::string> EaxPtrInitializer::MapKeyEaxPtrInitializerBases = {
	"[eax+%d]",
	"[eax + %d]",
	"[eax +%d]",
	"[eax+ %d]",
};
const std::string EaxPtrInitializer::MapKeyEaxPtrInitializer = "[eax]";

EaxPtrInitializer* EaxPtrInitializer::create(ValueMap& properties)
{
	EaxPtrInitializer* instance = new EaxPtrInitializer(properties);

	instance->autorelease();

	return instance;
}

EaxPtrInitializer::EaxPtrInitializer(ValueMap& properties) : super(properties)
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
