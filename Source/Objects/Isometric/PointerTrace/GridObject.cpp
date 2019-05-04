#include "GridObject.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

GridObject::GridObject(const ValueMap& properties) : super(properties)
{
	this->gridIndex = 0;
}

GridObject::~GridObject()
{
}

int GridObject::getGridIndex()
{
	return this->gridIndex;
}

void GridObject::setGridIndex(int gridIndex)
{
	this->gridIndex = gridIndex;
}
