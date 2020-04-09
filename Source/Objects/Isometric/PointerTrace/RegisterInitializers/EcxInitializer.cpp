#include "EcxInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EcxInitializer::MapKey = "ecx";

EcxInitializer* EcxInitializer::create(ValueMap& properties)
{
	EcxInitializer* instance = new EcxInitializer(properties);

	instance->autorelease();

	return instance;
}

EcxInitializer::EcxInitializer(ValueMap& properties) : super(properties)
{
}

EcxInitializer::~EcxInitializer()
{
}

void EcxInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	RegisterState::setRegisterEcx(gridIndex);	
}
