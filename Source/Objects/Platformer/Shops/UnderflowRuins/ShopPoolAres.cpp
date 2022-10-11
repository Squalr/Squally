#include "ShopPoolAres.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAres::MapKey = "shop-pool-ares";
const std::string ShopPoolAres::PoolName = "shop-pool-ares";

ShopPoolAres* ShopPoolAres::create(ValueMap& properties)
{
	ShopPoolAres* instance = new ShopPoolAres(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAres::ShopPoolAres(ValueMap& properties) : super(properties, ShopPoolAres::PoolName,
	{ CardPoolTier2::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolAres::~ShopPoolAres()
{
}
