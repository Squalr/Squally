#include "ShopPoolAlchT5.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAlchT5::MapKey = "shop-pool-alch-t5";
const std::string ShopPoolAlchT5::PoolName = "shop-pool-alch-t5";

ShopPoolAlchT5* ShopPoolAlchT5::create(ValueMap& properties)
{
	ShopPoolAlchT5* instance = new ShopPoolAlchT5(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAlchT5::ShopPoolAlchT5(ValueMap& properties) : super(properties, ShopPoolAlchT5::PoolName,
	{ })
{
	this->addItemToPool(ItemChance::create(BlackMushroom::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Mandrake::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Stinger::create(), ItemChance::Probability::Guaranteed));

	// Phasing out
	this->addItemToPool(ItemChance::create(GoldWeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(RatTail::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Pepper::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolAlchT5::~ShopPoolAlchT5()
{
}
