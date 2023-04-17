#include "ShopPoolAlchT6.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAlchT6::MapKey = "shop-pool-alch-t6";
const std::string ShopPoolAlchT6::PoolName = "shop-pool-alch-t6";

ShopPoolAlchT6* ShopPoolAlchT6::create(ValueMap& properties)
{
	ShopPoolAlchT6* instance = new ShopPoolAlchT6(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAlchT6::ShopPoolAlchT6(ValueMap& properties) : super(properties, ShopPoolAlchT6::PoolName,
	{ })
{
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolAlchT6::~ShopPoolAlchT6()
{
}
