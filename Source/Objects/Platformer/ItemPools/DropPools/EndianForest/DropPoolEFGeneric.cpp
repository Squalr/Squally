#include "DropPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolEFGeneric::PoolName = "ef-generic";

DropPoolEFGeneric* DropPoolEFGeneric::create(ValueMap& properties)
{
	DropPoolEFGeneric* instance = new DropPoolEFGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolEFGeneric::DropPoolEFGeneric(ValueMap& properties) : super(properties, DropPoolEFGeneric::PoolName, 1, 2, CardPoolTier1Rare::create())
{
	this->addItemToPool(HealthPotion::create(), 1.0f);
	this->addItemToPool(ManaPotion::create(), 1.0f);
	this->addItemToPool(WoodenMallet::create(), 0.01f);
	this->addItemToPool(WoodCutter::create(), 0.01f);
	this->addItemToPool(WoodenWand::create(), 0.01f);
	this->addItemToPool(CompositeBow::create(), 0.01f);
}

DropPoolEFGeneric::~DropPoolEFGeneric()
{
}

void DropPoolEFGeneric::onEnter()
{
	super::onEnter(); 
}

void DropPoolEFGeneric::initializePositions()
{
	super::initializePositions();
}

void DropPoolEFGeneric::initializeListeners()
{
	super::initializeListeners();
}
