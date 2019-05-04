#include "RegisterMarker.h"

#include "cocos/base/CCValue.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

RegisterMarker::RegisterMarker() : super(ValueMap())
{
}

RegisterMarker::~RegisterMarker()
{
}

void RegisterMarker::moveToRegister(MemoryGrid* memoryGrid)
{
	this->setPosition(memoryGrid->gridIndexToRelativePosition(this->getRegisterIndex()));
}
