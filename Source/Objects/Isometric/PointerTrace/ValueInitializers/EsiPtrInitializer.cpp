#include "EsiPtrInitializer.h"

#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::vector<std::string> EsiPtrInitializer::MapKeyEsiPtrInitializerBases = {
	"[esi+%d]",
	"[esi + %d]",
	"[esi +%d]",
	"[esi+ %d]",
};
const std::string EsiPtrInitializer::MapKeyEsiPtrInitializer = "[esi]";

EsiPtrInitializer* EsiPtrInitializer::create(ValueMap& properties)
{
	EsiPtrInitializer* instance = new EsiPtrInitializer(properties);

	instance->autorelease();

	return instance;
}

EsiPtrInitializer::EsiPtrInitializer(ValueMap& properties) : super(properties)
{
}

EsiPtrInitializer::~EsiPtrInitializer()
{
}

void EsiPtrInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(RegisterState::getRegisterEsi() + this->offset, gridIndex));
}
