#include "EaxInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EaxInitializer::MapKeyEaxInitializer = "eax";

EaxInitializer* EaxInitializer::create(ValueMap& properties)
{
	EaxInitializer* instance = new EaxInitializer(properties);

	instance->autorelease();

	return instance;
}

EaxInitializer::EaxInitializer(ValueMap& properties) : super(properties)
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
