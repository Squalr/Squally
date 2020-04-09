#include "EsiInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EsiInitializer::MapKey = "esi";

EsiInitializer* EsiInitializer::create(ValueMap& properties)
{
	EsiInitializer* instance = new EsiInitializer(properties);

	instance->autorelease();

	return instance;
}

EsiInitializer::EsiInitializer(ValueMap& properties) : super(properties)
{
}

EsiInitializer::~EsiInitializer()
{
}

void EsiInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	RegisterState::setRegisterEsi(gridIndex);	
}
