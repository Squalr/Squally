#include "DropPoolError.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolError::PoolName = "error";

DropPoolError* DropPoolError::create(ValueMap& properties)
{
	DropPoolError* instance = new DropPoolError(properties);

	instance->autorelease();

	return instance;
}

DropPoolError::DropPoolError(ValueMap& properties) : super(properties, DropPoolError::PoolName, SampleMethod::Guarantee, 1, 1)
{
	this->addItemToPool(ItemChance::create(MissingNo::create(), ItemChance::Probability::Guaranteed));
}

DropPoolError::~DropPoolError()
{
}

void DropPoolError::onEnter()
{
	super::onEnter(); 
}

void DropPoolError::initializePositions()
{
	super::initializePositions();
}

void DropPoolError::initializeListeners()
{
	super::initializeListeners();
}
