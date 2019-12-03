#include "PocketPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
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

PocketPoolEFGeneric::PocketPoolEFGeneric(ValueMap& properties) : super(properties, PocketPoolEFGeneric::PoolName, SampleMethod::Guarantee, 1, 1)
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(WoodenMallet::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(WoodCutter::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(WoodenWand::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(CompositeBow::create(), ItemChance::Probability::Uncommon));
}

PocketPoolEFGeneric::~PocketPoolEFGeneric()
{
}
