#include "EbpInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EbpInitializer::MapKey = "ebp";

EbpInitializer* EbpInitializer::create(ValueMap& properties)
{
	EbpInitializer* instance = new EbpInitializer(properties);

	instance->autorelease();

	return instance;
}

EbpInitializer::EbpInitializer(ValueMap& properties) : super(properties)
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
