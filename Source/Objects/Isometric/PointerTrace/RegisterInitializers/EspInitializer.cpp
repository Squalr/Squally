#include "EspInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EspInitializer::MapKey = "esp";

EspInitializer* EspInitializer::create(ValueMap& properties)
{
	EspInitializer* instance = new EspInitializer(properties);

	instance->autorelease();

	return instance;
}

EspInitializer::EspInitializer(ValueMap& properties) : super(properties)
{
}

EspInitializer::~EspInitializer()
{
}

void EspInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	RegisterState::setRegisterEsp(gridIndex);	
}
