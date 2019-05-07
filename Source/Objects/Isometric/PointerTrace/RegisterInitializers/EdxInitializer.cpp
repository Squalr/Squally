#include "EdxInitializer.h"

#include "Scenes/PointerTrace/RegisterState.h"

using namespace cocos2d;

const std::string EdxInitializer::MapKeyEdxInitializer = "edx";

EdxInitializer* EdxInitializer::create(ValueMap& initProperties)
{
	EdxInitializer* instance = new EdxInitializer(initProperties);

	instance->autorelease();

	return instance;
}

EdxInitializer::EdxInitializer(ValueMap& initProperties) : super(initProperties)
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
