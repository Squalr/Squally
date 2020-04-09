#include "EdxInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EdxInitializer::MapKey = "edx";

EdxInitializer* EdxInitializer::create(ValueMap& properties)
{
	EdxInitializer* instance = new EdxInitializer(properties);

	instance->autorelease();

	return instance;
}

EdxInitializer::EdxInitializer(ValueMap& properties) : super(properties)
{
}

EdxInitializer::~EdxInitializer()
{
}

void EdxInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	RegisterState::setRegisterEdx(gridIndex);	
}
