#include "EaxInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EaxInitializer::MapKeyEaxInitializer = "eax";

EaxInitializer* EaxInitializer::create(ValueMap& initProperties)
{
	EaxInitializer* instance = new EaxInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EaxInitializer::EaxInitializer(ValueMap& initProperties) : super(initProperties)
{
}

EaxInitializer::~EaxInitializer()
{
}

void EaxInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	RegisterState::setRegisterEax(gridIndex);	
}
