#include "DropPoolError.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
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

DropPoolError::DropPoolError(ValueMap& properties) : super(properties, DropPoolError::PoolName, 1, 3, CardPoolTier1::create())
{
	this->addItemToPool(HealthPotion::create(), 1.0f);
	this->addItemToPool(ManaPotion::create(), 1.0f);
	this->addItemToPool(WoodenMallet::create(), 0.01f);
	this->addItemToPool(WoodCutter::create(), 0.01f);
	this->addItemToPool(WoodenWand::create(), 0.01f);
	this->addItemToPool(CompositeBow::create(), 0.01f);
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
