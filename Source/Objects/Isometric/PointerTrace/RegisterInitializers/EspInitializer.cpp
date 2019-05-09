#include "EspInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EspInitializer::MapKeyEspInitializer = "esp";

EspInitializer* EspInitializer::create(ValueMap& initProperties)
{
	EspInitializer* instance = new EspInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EspInitializer::EspInitializer(ValueMap& initProperties) : super(initProperties)
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
