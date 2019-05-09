#include "EbxInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EbxInitializer::MapKeyEbxInitializer = "ebx";

EbxInitializer* EbxInitializer::create(ValueMap& initProperties)
{
	EbxInitializer* instance = new EbxInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EbxInitializer::EbxInitializer(ValueMap& initProperties) : super(initProperties)
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
