#include "EbxPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::vector<std::string> EbxPtrInitializer::MapKeyEbxPtrInitializerBases = {
	"[ebx+%d]",
	"[ebx + %d]",
	"[ebx +%d]",
	"[ebx+ %d]",
};
const std::string EbxPtrInitializer::MapKeyEbxPtrInitializer = "[ebx]";

EbxPtrInitializer* EbxPtrInitializer::create(ValueMap& properties)
{
	EbxPtrInitializer* instance = new EbxPtrInitializer(properties);

	instance->autorelease();

	return instance;
}

EbxPtrInitializer::EbxPtrInitializer(ValueMap& properties) : super(properties)
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
