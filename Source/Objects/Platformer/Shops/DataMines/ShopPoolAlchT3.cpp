#include "ShopPoolAlchT3.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAlchT3::MapKey = "shop-pool-alch-t3";
const std::string ShopPoolAlchT3::PoolName = "shop-pool-alch-t3";

ShopPoolAlchT3* ShopPoolAlchT3::create(ValueMap& properties)
{
	ShopPoolAlchT3* instance = new ShopPoolAlchT3(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAlchT3::ShopPoolAlchT3(ValueMap& properties) : super(properties, ShopPoolAlchT3::PoolName,
	{ })
{
	// Phasing out
	this->addItemToPool(ItemChance::create(Acorn::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Guaranteed));

	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SandRoot::create(), ItemChance::Probability::Guaranteed));

	// Phasing in
	this->addItemToPool(ItemChance::create(GoldWeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(RatTail::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolAlchT3::~ShopPoolAlchT3()
{
}
