#include "ShopPoolFraya.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolFraya::MapKey = "shop-pool-fraya";
const std::string ShopPoolFraya::PoolName = "shop-pool-fraya";

ShopPoolFraya* ShopPoolFraya::create(ValueMap& properties)
{
	ShopPoolFraya* instance = new ShopPoolFraya(properties);

	instance->autorelease();

	return instance;
}

ShopPoolFraya::ShopPoolFraya(ValueMap& properties) : super(properties, ShopPoolFraya::PoolName,
	{ })
{
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolFraya::~ShopPoolFraya()
{
}
