#include "EcxInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EcxInitializer::MapKeyEcxInitializer = "ecx";

EcxInitializer* EcxInitializer::create(ValueMap& initProperties)
{
	EcxInitializer* instance = new EcxInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EcxInitializer::EcxInitializer(ValueMap& initProperties) : super(initProperties)
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
