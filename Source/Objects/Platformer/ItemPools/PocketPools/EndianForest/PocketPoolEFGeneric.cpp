#include "PocketPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolEFGeneric::PoolName = "ef-generic";

PocketPoolEFGeneric* PocketPoolEFGeneric::create(ValueMap& properties)
{
	PocketPoolEFGeneric* instance = new PocketPoolEFGeneric(properties);

	instance->autorelease();

	return instance;
}

PocketPoolEFGeneric::PocketPoolEFGeneric(ValueMap& properties) : super(properties, PocketPoolEFGeneric::PoolName, 1, 1)
{
	this->addItemToPool(HealthPotion::create(), 1.0f);
	this->addItemToPool(ManaPotion::create(), 1.0f);
	this->addItemToPool(WoodenMallet::create(), 1.0f);
	this->addItemToPool(WoodCutter::create(), 0.15f);
	this->addItemToPool(WoodenWand::create(), 0.15f);
	this->addItemToPool(CompositeBow::create(), 0.15f);
}

PocketPoolEFGeneric::~PocketPoolEFGeneric()
{
}
