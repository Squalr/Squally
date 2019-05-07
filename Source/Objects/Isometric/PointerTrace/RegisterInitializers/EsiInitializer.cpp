#include "EsiInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EsiInitializer::MapKeyEsiInitializer = "esi";

EsiInitializer* EsiInitializer::create(ValueMap& initProperties)
{
	EsiInitializer* instance = new EsiInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EsiInitializer::EsiInitializer(ValueMap& initProperties) : super(initProperties)
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
