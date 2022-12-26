#include "ShopPoolInnT6.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolInnT6::MapKey = "shop-pool-inn-t6";
const std::string ShopPoolInnT6::PoolName = "shop-pool-inn-t6";

ShopPoolInnT6* ShopPoolInnT6::create(ValueMap& properties)
{
	ShopPoolInnT6* instance = new ShopPoolInnT6(properties);

	instance->autorelease();

	return instance;
}

ShopPoolInnT6::ShopPoolInnT6(ValueMap& properties) : super(properties, ShopPoolInnT6::PoolName,
	{ CardPoolTier3::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolInnT6::~ShopPoolInnT6()
{
}
