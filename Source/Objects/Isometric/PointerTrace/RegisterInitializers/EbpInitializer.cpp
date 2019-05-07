#include "EbpInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EbpInitializer::MapKeyEbpInitializer = "ebp";

EbpInitializer* EbpInitializer::create(ValueMap& initProperties)
{
	EbpInitializer* instance = new EbpInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EbpInitializer::EbpInitializer(ValueMap& initProperties) : super(initProperties)
{
}

EbpInitializer::~EbpInitializer()
{
}

void EbpInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	RegisterState::setRegisterEbp(gridIndex);	
}
