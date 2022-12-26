#include "ShopPoolAlchT8.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAlchT8::MapKey = "shop-pool-alch-t8";
const std::string ShopPoolAlchT8::PoolName = "shop-pool-alch-t8";

ShopPoolAlchT8* ShopPoolAlchT8::create(ValueMap& properties)
{
	ShopPoolAlchT8* instance = new ShopPoolAlchT8(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAlchT8::ShopPoolAlchT8(ValueMap& properties) : super(properties, ShopPoolAlchT8::PoolName,
	{ })
{
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolAlchT8::~ShopPoolAlchT8()
{
}
