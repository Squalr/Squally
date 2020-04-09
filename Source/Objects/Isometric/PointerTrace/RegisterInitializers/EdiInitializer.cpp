#include "EdiInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EdiInitializer::MapKey = "edi";

EdiInitializer* EdiInitializer::create(ValueMap& properties)
{
	EdiInitializer* instance = new EdiInitializer(properties);

	instance->autorelease();

	return instance;
}

EdiInitializer::EdiInitializer(ValueMap& properties) : super(properties)
{
}

EdiInitializer::~EdiInitializer()
{
}

void EdiInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	RegisterState::setRegisterEdi(gridIndex);	
}
