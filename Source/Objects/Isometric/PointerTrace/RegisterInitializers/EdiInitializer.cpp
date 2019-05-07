#include "EdiInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EdiInitializer::MapKeyEdiInitializer = "edi";

EdiInitializer* EdiInitializer::create(ValueMap& initProperties)
{
	EdiInitializer* instance = new EdiInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EdiInitializer::EdiInitializer(ValueMap& initProperties) : super(initProperties)
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
