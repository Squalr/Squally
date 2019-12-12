#include "EmptyPool.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EmptyPool::PoolName = "empty";

EmptyPool* EmptyPool::create()
{
	EmptyPool* instance = new EmptyPool();

	instance->autorelease();

	return instance;
}

EmptyPool::EmptyPool() : super(ValueMap(), EmptyPool::PoolName, SampleMethod::Guarantee, 0, 0)
{
}

EmptyPool::~EmptyPool()
{
}

void EmptyPool::onEnter()
{
	super::onEnter(); 
}

void EmptyPool::initializePositions()
{
	super::initializePositions();
}

void EmptyPool::initializeListeners()
{
	super::initializeListeners();
}
