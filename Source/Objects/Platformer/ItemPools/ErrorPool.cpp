#include "ErrorPool.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ErrorPool::PoolName = "error";

ErrorPool* ErrorPool::create()
{
	ErrorPool* instance = new ErrorPool();

	instance->autorelease();

	return instance;
}

ErrorPool::ErrorPool() : super(ValueMap(), ErrorPool::PoolName, SampleMethod::Guarantee, 1, 1)
{
	this->addItemToPool(ItemChance::create(MissingNo::create(), ItemChance::Probability::Guaranteed));
}

ErrorPool::~ErrorPool()
{
}

void ErrorPool::onEnter()
{
	super::onEnter(); 
}

void ErrorPool::initializePositions()
{
	super::initializePositions();
}

void ErrorPool::initializeListeners()
{
	super::initializeListeners();
}
