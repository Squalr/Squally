#include "EbxInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EbxInitializer::MapKey = "ebx";

EbxInitializer* EbxInitializer::create(ValueMap& properties)
{
	EbxInitializer* instance = new EbxInitializer(properties);

	instance->autorelease();

	return instance;
}

EbxInitializer::EbxInitializer(ValueMap& properties) : super(properties)
{
}

EbxInitializer::~EbxInitializer()
{
}

void EbxInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	RegisterState::setRegisterEbx(gridIndex);	
}
