#include "EdxPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::vector<std::string> EdxPtrInitializer::MapKeyEdxPtrInitializerBases = {
	"[edx+%d]",
	"[edx + %d]",
	"[edx +%d]",
	"[edx+ %d]",
};
const std::string EdxPtrInitializer::MapKeyEdxPtrInitializer = "[edx]";

EdxPtrInitializer* EdxPtrInitializer::create(ValueMap& properties)
{
	EdxPtrInitializer* instance = new EdxPtrInitializer(properties);

	instance->autorelease();

	return instance;
}

EdxPtrInitializer::EdxPtrInitializer(ValueMap& properties) : super(properties)
{
}

EdxPtrInitializer::~EdxPtrInitializer()
{
}

void EdxPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEdx() + this->offset, gridIndex));
}
